#include <iostream>
#include "AVLTree.h"
#include "AbstractTable.h"
#include "ChainedHashTable.h"
#include "Polynomial.h"
#include "OrderedListBasedTable.h"
#include "UnorderedArrayBasedTable.h"
#include "UnorderedListBasedTable.h"

   

void main()
{
	UnorderedABTable<int, Polynomial> table1;
	Polynomial polynom1("1*x^2*y^2*z^2");
	polynom1.toPolynom();
	Polynomial polynom2("2*x^3*y^3*z^3");
	polynom2.toPolynom();
	table1.Insert(2, polynom1);
	table1.Insert(1, polynom2);
	List<Record<int, Polynomial>> record1 = table1.GetRecords();
	for (auto it = record1.Begin(); it != record1.End(); it++)
	{
		std::cout << it.target->value.key << "\t" << it.target->value.val << std::endl;
	}
	std::cout << std::endl;


	UnorderedLBTable<int, Polynomial> table2;
	table2.Insert(2, polynom1);
	table2.Insert(1, polynom2);
	List<Record<int, Polynomial>> record2 = table2.GetRecords();
	for (auto it = record2.Begin(); it != record2.End(); it++)
	{
		std::cout << it.target->value.key << "\t" << it.target->value.val << std::endl;
	}
	std::cout << std::endl;


	OrderedListTable<int, Polynomial> table3;
	table3.Insert(2, polynom1);
	table3.Insert(1, polynom2);
	List<Record<int, Polynomial>> record3 = table3.GetRecords();
	for (auto it = record3.Begin(); it != record3.End(); it++)
	{
		std::cout << it.target->value.key << "\t" << it.target->value.val << std::endl;
	}
	std::cout << std::endl;

	ChainedHashTable<int, Polynomial> table4;
	table4.Insert(2, polynom1);
	table4.Insert(1, polynom2);
	std::cout << "1\t" << table4.SearchByKey(1) << std::endl << "2\t" << table4.SearchByKey(2) << std::endl << std::endl;

	AVLTree<int, Polynomial> table5;
	table5.Insert(2, polynom1);
	table5.Insert(1, polynom2);
	std::cout << "1\t" << table4.SearchByKey(1) << std::endl << "2\t" << table4.SearchByKey(2);
}