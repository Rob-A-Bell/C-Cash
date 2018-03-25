/**
 *  BlockChain ADT : private implementation / algorithms
 *
 *  COMP220: Assignment 3
 *  Author:  
 *  Date:    Feb. 1, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <assert.h>

#include "trnslist.h"
#include "puzzle.h"
#include "block.h"
#include "blockchain.h"

/***********************
 * BLOCKCHAIN private implementation details
 ***********************/
const int DEFAULT_DIFFICULTY = 2;              // Default difficulty for hashing puzzles, increase to make mining harder

/*********************
 *  PUBLIC INTERFACE
 *********************/
 
/*
 * Constructor - return a new, empty BlockChain 
 * POST:  bcLen(chain) == 0
 */
BlockChain bcNew()
{	
	TransactionList tlist = tlistCreate();
	BlockChain blockchain; 
	Block_t* GENESIS = blkCreate(tlist,DEFAULT_DIFFICULTY, NULL_NONCE);
	blockchain.head = GENESIS;
	blockchain.tail = GENESIS;
	blkComputeHash(GENESIS);
	//ID == 0 FROM THE BLOCKCREATE FUNCTION IN BLOCK.C
	//NEXT AND PREV == NULL FROM BLOCK CREATE
	return blockchain;
}

/*
 * Destructor - remove all data and free all memory associated with the chain 
 * POST: bcLen(chain) == 0
 */
void bcDelete( BlockChain *chain )
{
	while(chain->head != chain->tail)
	{
		chain->head = chain->head->next;
		free(chain->head->prev);
	}
	chain->head = NULL;
	chain->tail = NULL;
	chain = NULL;
}

/*
 * Returns bool value whether blockchain is empty
 */
 //whats the definition of empty? deleted? because bc delete frees chain 
 //oh shit
bool bcExists(BlockChain *chain) 
{
	if(chain == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool bcisEmpty(BlockChain *chain) 
{
	if(chain->head->next == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
 * Print a text representation of this chain on STDOUT
 */
void bcPrint( const BlockChain chain )
{
	Block_t* cur = chain.head;
	printf("Printing BlockChain \n\n");
	while(cur != NULL){
		blkPrint(*cur);
		cur = cur->next;
		printf("\n");

	}
}

void blkPrint(Block_t block)
{

   printf("Block ID:  %d \n", block.id );
   tlistPrint(block.transactions);
   if(block.prev != NULL)
   printHash(block.hash);
   
   printf("Nonce:%lu\n", block.proof_of_work.i_nonce);
   printf("difficulty: %d\n", block.difficulty);

}
/*
 * Return the number of Blocks in the chain
 */
int bcLen( const BlockChain chain )
{
	int len = 0;
	Block_t* cur = chain.head;
	while(cur != NULL){
		len++;
		cur = cur->next;
	}
	return len;
}

/*
 *  Return true iff blkIsValid(block) for every block in the chain
 */
bool blkCIsValid(const BlockChain chain)
{
	Block_t* cur = chain.head->next;
	while(cur!= NULL){
	if(!blkValidates(*cur,cur->prev->hash, cur->proof_of_work)){
		printf("A block in the chain was not vaildated");
		return false;
		}
		cur = cur->next;
	}
		printf("All the blocks were validated!\n");
		return true;
}

/*
 * Return a pointer to the chain's tail Block
 */
Block_t* bcTail(const BlockChain chain)
{
	Block_t* cur = chain.tail;
	return cur; 
}

/*
 * Append the given block to the chain 
 *    iff blkValidates(new_block, bcTail->hash, new_block->proof_of_work)
 * POST: bcTail(*chain) == new_block && blkIsValid(*new_block)
 */
void bcAppend( BlockChain *chain, Block_t* new_block )
{	
	 blkChainTo(chain->tail, new_block);
	 chain->tail = new_block;
	 chain->tail->next = NULL;
}

void bcPrepblk( Block_t* block, BlockChain chain, Nonce_t nonce)
{
	
//	assert(blkValidates(*block, chain.tail->hash, nonce));
	
	//ASSIGN THE NONCE TO THE BLOCK  
	block->proof_of_work = nonce;
	blkComputeHash(block);
	
}




