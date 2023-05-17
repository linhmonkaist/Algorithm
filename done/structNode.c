/* 
 * csim.c - A cache simulator that can replay traces from Valgrind
 *     and output statistics such as number of hits, misses, and
 *     evictions.  The reference replacement policy is LRU.
 *
 * Implementation and assumptions:
 *  1. Each load/store can cause at most one cache miss. 
 *  2. All implementations not using cache concept will get no point.
 *  3. If you fail to pass these cache validation steps, then you will get no point. We check cache validity in two aspects:
 *     1) Cold miss must not exceed available amount (proportional to cache size).
 *     2) When L1 cache miss ocurred, you must access L2 cache.
 *  4. If you miss to manage memory allocation (e.g. not freeing malloc’d memory), then you will get -10pt penalty.
 *
 */
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include "csim.h"

/* The cache we are simulating */
cache_t l1_cache;
cache_t l2_cache;
mem_addr_t l1_set_index_mask;
mem_addr_t l2_set_index_mask;

extern cache_config_t l1_config;
extern cache_config_t l2_config;

unsigned long long int lru_counter_l1 = 1;
unsigned long long int lru_counter_l2 = 1;

typedef side_link{
    int index;
    struct side_link* prev;
    struct side_link* next;
} side_link;

side_link* l1_side;
side_link* l2_side;

void swap(cache_line_t a, cache_line_t b){
    cache_line_t p;
    p= a;
    a=b;
    b=p;
}

/*
 * initCache - Allocate memory, write 0's for valid and tag and LRU
 * also computes the set_index_mask
 */
void initCache()
{   
    l1_side= (side_link*) malloc(sizeof(side_link)*l1_config.S);
    l2_side= (side_link*) malloc(sizeof(side_link)*l2_config.S);

    l1_cache= (cache_set_t*) malloc(sizeof(cache_line_t)*l1_config.S);
    for (int i=0; i< l1_config.S; i++){
        l1_cache[i]= (cache_line_t*) malloc(sizeof(cache_line_t)*l1_config.E);
        l1_side[i]= (side_link*) malloc(sizeof(side_link)*l1_config.S);
        for(int j=0; j< l1_config.E;j++){
            l1_cache[i][j].valid= '0';
            l1_cache[i][j].tag= 0;
            l1_cache[i][j].lru=0;
            l1_side[i][j].index= l1_cache[i][j];
            l1_side[i][j].prev= &l1_side[i][j-1];
            l1_side[i][j].next= &l1_side[i][j+1];
        }
        l1_side[i][0].prev= NULL;
        l1_side[i][l1_config.E-1].next = NULL;
        
    }
    l1_set_index_mask= ((1 << l1_config.s)-1) << l1_config.b;
    
    l2_cache= (cache_set_t*) malloc(sizeof(cache_line_t)*l2_config.S);
    for (int i=0; i< l2_config.S; i++){
        l2_cache[i]= (cache_line_t*) malloc(sizeof(cache_line_t)*l2_config.E);
        l2_side[i]= (side_link*) malloc(sizeof(side_link)*l2_config.S);
        for(int j=0; j< l2_config.E;j++){
            l2_cache[i][j].valid= '0';
            l2_cache[i][j].tag= 0;
            l2_cache[i][j].lru=0;
            l2_side[i][j].index= l2_cache[i][j];
            l2_side[i][j].prev= &l2_side[i][j-1];
            l2_side[i][j].next= &l2_side[i][j+1];
        }
        l2_side[i][0].prev= NULL;
        l2_side[i][l1_config.E-1].next = NULL;
    }
    l2_set_index_mask= ((1 << l2_config.s)-1) << l2_config.b;

}

void insert(side,i,index){
    cache_line_t temp= side[index][i];
    side[index][i].prev= 
}

/* 
 * accessData - Access data at memory address addr.
 *   If it is already in L1 cache, increast L1 hit count
 *   If it is not in L1 cache, bring it in cache, increase L1 miss count.
 *   Also increase L1 eviction count if a line is evicted.
 *   If data is not in L1 cache, search for L2 cache.
 *   If it is in L2 cache, increast L2 hit count
 *   If it is not in L2 cache, bring it in cache, increase L2 miss count.
 *   Also increase L2 eviction count if a line is evicted.
 */
access_record_t accessData(mem_addr_t addr)
{
    access_record_t access_record = {0, 0, 0, 0, 0, 0};
    mem_addr_t tag= addr >> (l1_config.b+l1_config.s);
    mem_addr_t set_index= (addr & l1_set_index_mask) >> l1_config.b;
    mem_addr_t l2_tag= addr >> (l2_config.b+l2_config.s);
    mem_addr_t l2_set_index= (addr & l2_set_index_mask) >> l2_config.b;

    cache_line_t temp;
    //l1-hit
    for (int i=0; i< l1_config.E;i++){
        if ((l1_side[set_index][i].tag == tag) && (l1_side[set_index][i].valid=='1')){      //same tag and valid ==1
            access_record.l1_hit +=1;
            l1_cache[set_index][i].lru +=1;
            temp= l1_side[set_index][0];
            for (int j= l1_config.E-1; j>0 ;j--){
                l1_cache[set_index][j]= l1_cache[set_index][j-1];
            }
            l1_cache[set_index][0]= temp;
            return access_record;
        }
    }
    //l1-miss
    access_record.l1_miss +=1;
    for (int i=0; i< l2_config.E;i++){
        if ((l2_cache[l2_set_index][i].tag == l2_tag) && (l2_cache[l2_set_index][i].valid== '1')){      //same tag and valid ==1
            access_record.l2_hit +=1;                                                           //l2-hit, evic l1
            l2_cache[l2_set_index][i].lru = +1;
            temp= l2_cache[l2_set_index][i];
            for (int j= l2_config.E-1; j>0 ;j--){
                l2_cache[l2_set_index][j]= l2_cache[l2_set_index][j-1];
            }
            l2_cache[l2_set_index][0]= temp;

            access_record.l1_eviction +=1;
            
            l1_cache[set_index][hold].valid= '1';
            l1_cache[set_index][hold].tag= tag;
            l1_cache[set_index][hold].lru= 1; 
            return access_record;
        }
    }
    access_record.l2_miss +=1;
    access_record.l1_eviction +=1;
    access_record.l2_eviction +=1;
    //min_lru= l2_cache[l2_set_index][0].lru;
    
    if (l2_rank[l2_set_index] == l2_config.E){hold= l2_rank[l2_set_index]-1;}
    else {hold= l2_rank[l2_set_index]; l2_rank[l2_set_index] += 1;}
    /*hold= 0;
    for (int i=0; i< l2_config.E;i++){
        if (l2_cache[l2_set_index][i].lru < min_lru){
            min_lru= l2_cache[l2_set_index][i].lru;
            hold= i;
        }
    }*/
    l2_cache[l2_set_index][hold].valid= '1';
    l2_cache[l2_set_index][hold].tag= l2_tag;
    l2_cache[l2_set_index][hold].lru=1;
    if (l1_rank[set_index] == l1_config.E){hold= l1_rank[set_index]-1;}
    else {hold= l1_rank[set_index]; l1_rank[set_index] += 1;}
    /*min_lru= l1_cache[set_index][0].lru;
    hold=0;
    for (int i=0; i< l1_config.E;i++){
        if (l1_cache[set_index][i].lru < min_lru){
            min_lru= l1_cache[set_index][i].lru;
            hold= i;
        }
    }*/
    l1_cache[set_index][hold].valid= '1';
    l1_cache[set_index][hold].tag= tag;
    l1_cache[set_index][hold].lru= 1; 
    /*if (l1_rank[set_index] < l1_config.E-1){l1_rank[set_index] +=1;}
    hold= l1_rank[set_index];
    l1_cache[set_index][hold].valid= '1';
    l1_cache[set_index][hold].tag= tag;
    l1_cache[set_index][hold].lru= 1; */
    
    return access_record;
}

/*
 * freeCache - free allocated memory
 */
void freeCache()
{
    for (int i=0; i< l1_config.S; i++){
        free(l1_cache[i]);
    }
    free(l1_cache);
    for (int i=0; i< l2_config.S; i++){
        free(l2_cache[i]);
    }
    free(l2_cache);
}

