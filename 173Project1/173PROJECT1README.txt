
README for CSC173 Project 1 code


Collaborator: Ye Na Kang, Thu Hoang, Jiahao Lu



How to build our project:
	Files:
		dfa.h
		dfa.c
		nfa.h
		nfa.c
		nfatodfa.h
		nfatodfa.c
		main.c
		IntHashSet.h
		IntHashSet.c
		LinkedList.h
		LinkedList.c
		Makefile

		Our input alphabet contains the char value from 0 to 9 and lowercase a to z



How to run our projects:
 
	use command:  cl/gcc(compiler) main.c nfatodfa.c nfa.c dfa.c IntHashSet.c LinkedList.c to create main.exe

	In the main is a menu system: 
		Type suggested number to enter different machine. 
		For each part of NFA and DFA, either enter the string for machine to recognize or you can type quit so that the next part will come up. 
		For example, Type 2 for NFA, if you want to test the third part "washington" directly, input "quit" twice to exit the first two, then the menu will take you straight to the third part.


		

		Our 1(e) and 2(d) respectively accepts 
			1(e) any string that starts with 1 and ends with 0
			2(d) any string that ends with either elbow or below


		
		