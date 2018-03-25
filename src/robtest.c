/**
 *  BLOCKCHAIN : automatated unit test driver
 *
 *  COMP220: Assignment 3
 *  Author:  Robert Bell
 *  Date:    March 17, 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "trnslist.h"
#include "puzzle.h"
#include "block.h"
#include "blockchain.h"

const int SET_DIFFICULTY = 2;  

Nonce_t bcMine(Block_t block, Hash_t hash);

Nonce_t bcMine(Block_t block, Hash_t hash)
{	
	Puzzle_t puzzle = blkCreatePuzzle(block,hash);
	Nonce_t nonce = puzzleMine(puzzle);
	//return nonce;
} 



int main()
{
	
	//CREATE BLOCKCHAIN
	printf("\nEnter the Trading Platform!\n");
	BlockChain bobcoin = bcNew();
	printf("bobcoin created\n");

	char* CF = "Captain_Falcon";
	char* SA = "Samus_Aran";
	
	//MAKES TRANSACTION LIST
	TransactionList tlist1 = tlistCreate( );
	
	//APPENDS TRANSACTION LIST
	tlistAppend(&tlist1, CF, 20.75, SA);
	tlistAppend(&tlist1, CF, 400.25, SA);
	tlistAppend(&tlist1, SA, 321.01, CF);
	
	//MAKES NEW BLOCK
	Block_t *new_block = blkCreate(tlist1, SET_DIFFICULTY  , NULL_NONCE);
	
	//CREATE PUZZLE WITH A SERIALIZED BUFFER
	Puzzle_t new_puzzle = blkCreatePuzzle(*new_block, bobcoin.tail->hash);
	
	//MINE PUZZLE
	new_block->proof_of_work = puzzleMine(new_puzzle);
	
	//APPEND PUZZLE!!!
	bcAppend(&bobcoin, new_block);
	
	//PRINT BOBCOIN
	bcPrint(bobcoin);
	
	
	
	printf("\n\nROUND 2\n\n ");
	
	//MAKES TLIST
	TransactionList tlist2 = tlistCreate( );
	tlistAppend(&tlist2, CF, 650.45, SA);
	tlistAppend(&tlist2, CF, 2345.25, SA);
	tlistAppend(&tlist2, SA, 3881.01, CF);
//	tlistPrint(tlist2);
	
	
	//MAKES NEW BLOCK
	Block_t *new_block2 = blkCreate(tlist2, SET_DIFFICULTY, NULL_NONCE);
	

	//CREATE PUZZLE WITH A SERIALIZED BUFFER
	Puzzle_t new_puzzle2 = blkCreatePuzzle(*new_block2, bobcoin.tail->hash);
	
	
	//MINE PUZZLE
	new_block2->proof_of_work = puzzleMine(new_puzzle2);
	
	// //APPEND PUZZLE!!!
	 bcAppend(&bobcoin, new_block2);
	
	
	//PRINT BOBCOIN
	bcPrint(bobcoin);
	blkCIsValid(bobcoin);
	bcDelete(&bobcoin);
	if(bcExists(bobcoin)){
		printf("\nbobcoin deleted.");
	}
	else{
		printf("\nThat didn't delete properly.");
	}
		return 0;
}
