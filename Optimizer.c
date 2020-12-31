/*
 *********************************************
 *  314 Principles of Programming Languages  *
 *  Spring 2014                              *
 *  Authors: Ulrich Kremer                   *
 *           Hans Christian Woithe           *
 *********************************************
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

void critical_L(Instruction *current);
void criticalarth(Instruction *current);

int main()
{
	Instruction *head;

	//flag for critical identity
	//int flag;


	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	/* YOUR CODE GOES HERE --WORKING ON IT--*/

	//Point current pointer to the head
	Instruction *current = head;
	
	//check for all Read and Write
	while (current)
	{
		if ((current ->opcode == WRITE) || (current ->opcode == READ))
		{
			current->critical = 'c';	//flag for critical
		}

		current = current->next;
	}
	//All READ and WRITE are marked critical

	//Find STORE now
	while (current)
	{
		if (current->opcode == STORE)
		{
			current -> critical = 'c';	//flag for critical
		}

		current = current->prev;
		
	}
	//ALL STORE are marked critical

	//Now found rest of the instructions
	current = LastInstruction(head);
	while (current)
	{
		if (current->critical == 'c')
		{
			switch (current->opcode)
			{
			case ADD:
			case SUB:
			case MUL:
			case AND:
			case OR:
				criticalarth(current);
			case LOAD:
			case LOADI:
			case READ:
			case STORE:
			case WRITE:
				critical_L(current);
			}
		}

		current = current->prev;
	}



	//remove non-criticals
	while (current)
	{
		if (current->critical != 'c')
		{
			free(current);
		}

		current = current->next;
		
	}

	if (head) {
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}

//Call critical_L function
	void critical_L(Instruction *current){
		while (current->opcode == WRITE)
		{
			current = current->prev;
		}
		
		int target;
		target = current->field1;
		Instruction *previous = current->prev;
		if(previous && previous->critical != 'c'){
			switch (previous->opcode)
			{
				case LOAD:
				case LOADI:
				case ADD:
				case SUB:
				case MUL:
				case AND:
				case OR:
				case STORE:
					if (previous->field1 == target)
					{
						previous->critical = 'c';
					}
			        case READ:
		 	        case WRITE:
				        break;


			}
		}
		
	}

	void criticalarth(Instruction *current){
		
		int target1, target2;
		target1 = current->field2;
		target2 = current->field3;
		Instruction *previous = current->prev;

		if(previous && previous->critical != 'c'){
			switch (previous->opcode)
			{
				case LOAD:
				case LOADI:
				case ADD:
				case SUB:
				case MUL:
				case AND:
				case OR:
				case STORE:
					if ((previous->field1 == target1) ||(previous->field1 == target2))
					{
						previous->critical = 'c';
					}
			        case READ:
		 	        case WRITE:
				        break;
			}
		}
	}


	
	



