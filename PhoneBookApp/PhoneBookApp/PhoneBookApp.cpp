// PhoneBookApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <string>
#include <regex>

using namespace std;



class Contact
{
	public:
		string ContactName;
		list<string> ContactNo;
};

class PhoneBookMethods 
{
	public:

		//Member Variables
		string PhoneNo;
		list<Contact> Contacts;
		Contact ObjContact;

		//Get Input
		double NoOfContacts();
		string GetName();
		string GetNo();

		//Main Functionalities
		void AddContacts();
		void DisplayContacts();
		void UpdateContact();
		void DeleteContact();
		void SearchContact();

		//Sub Functionalities
		void AddNewContact(Contact&);
		int DisplaySpecificContacts(string);
		void UpdateContactDetails(string, char);
		void DeleteContactDetails(string, char);

		//Extras
		char MergeContacts(string);
		bool CheckExistingContact(string);
		void FillPhoneBook();
		int SearchByName(string);
};


bool SortMethod(Contact a, Contact b);

int j{ 0 };
int main()
{
	PhoneBookMethods ObjPhoneBookMethods;
	//ObjPhoneBookMethods.FillPhoneBook();
	char choice{ '0' };
	while (choice != '6')
	{
		cout << "\n\n\t\b\b\b======================================================================";
		cout << "\n\n\t\b\b\b~~~~~~~~~~~~~~~~~~~~~~~~~~     MAIN MENU     ~~~~~~~~~~~~~~~~~~~~~~~~~";
		cout << "\n\n\t\b\b\b======================================================================";
		cout << "\n\n\t\t\t        Choose an option:\n\n\t\t\t        1. Add Contact(s)\n\n\t\t\t        2. Display Contacts\n\n\t\t\t        3. Update Contact\n\n\t\t\t        4. Delete Contact\n\n\t\t\t        5. Search Contact\n\n\t\t\t        6. Exit\n\n\t\t\t        Enter your choice: ";
		(cin >> choice).get();
		switch (choice)
		{
		case '1'://Add Contact(s)
			system("cls");
			ObjPhoneBookMethods.AddContacts();
			cout << "\n\n\t\t\b\b\b";
			system("pause");
			system("cls");
			break;

		case '2':// Display Contacts
			system("cls");
			ObjPhoneBookMethods.Contacts.sort(SortMethod);
			ObjPhoneBookMethods.DisplayContacts();
			cout << "\n\n\t\t\b\b\b";
			system("pause");
			system("cls");
			break;

		case '3'://Update Contact
			system("cls");
			ObjPhoneBookMethods.UpdateContact();
			system("cls");
			break;

		case '4'://Delete Contact
			system("cls");
			ObjPhoneBookMethods.DeleteContact();
			system("cls");
			break;

		case '5'://Search Contact
			system("cls");
			ObjPhoneBookMethods.SearchContact();
			system("cls");
			break;

		case '6'://Exit
			break;

		default:
			system("cls");
			cout << "\n\tPlease choose a correct option.\n";
			break;
		}
	}
	return 0;
}




double PhoneBookMethods::NoOfContacts() // Takes No. of entries/contacts to be added.
{
	double NoOfEntries;
	while ((cout << "\n\n\t\tEnter the no. of entries to be made: ") && !(cin >> NoOfEntries) || (NoOfEntries < 0))
	{
		cout << "\n\t\t\tPlease enter a valid number.";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return NoOfEntries;
}

string PhoneBookMethods::GetName()//Input Name
{
	string FName, LName, Name;
	cout << "\n\n\t\tEnter First Name: ";
	cin >> FName;
	cin.ignore();
	cout << "\n\n\t\tEnter Last Name: ";
	getline(cin, LName, '\n');
	Name = (FName + " " + LName);
	transform(Name.begin(), Name.end(), Name.begin(), toupper);

	return Name;
}

string PhoneBookMethods::GetNo()//Input No
{
	string PhoneNo;
	cout << "\n\n\t\tEnter Phone No.: ";
	regex r("^(([0]|(\\+91-)|(\\+91))\\d{10})|\\d{10}$");
	cin >> PhoneNo;
	while (!regex_match(PhoneNo, r))
	{
		cout << "\n\n\t\tPlease Enter a valid no.";
		cout << "\n\n\t\tEnter Phone No.: ";
		cin >> PhoneNo;
	}
	if (PhoneNo.at(0) == '+' && PhoneNo.length() > 10)
	{
		if (PhoneNo.at(3) == '-')
		{

		}
		else
		{
			PhoneNo.replace(0, 3, "+91-");
		}
	}
	if (PhoneNo.at(0) == '0')
	{
		PhoneNo.replace(0, 1, "+91-");
	}
	if (PhoneNo.at(0) != '0' && PhoneNo.at(0) != '+')
	{
		PhoneNo = "+91-" + PhoneNo;
	}
	return PhoneNo;
}

bool SortMethod(Contact a, Contact b) //Sorting of Contacts
{
	if (a.ContactName == b.ContactName)
	{
		return a.ContactNo < b.ContactNo;
	}
	else
	{
		return a.ContactName < b.ContactName;
	}
}






void PhoneBookMethods::AddContacts() // Adding Contacts
{
	cout << "\n\n\t\b\b\b======================================================================";
	cout << "\n\n\t\b\b\b~~~~~~~~~~~~~~~~~~~~~~~~~     ADD CONTACT     ~~~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\n\n\t\b\b\b======================================================================";
	char ch{ 'a' };
	int temp = (int)NoOfContacts();
	int i;
	for (i = 1; i <= temp; i++)
	{
		cout << "\n\n\t\tEntry No. " << i;
		Contact AddContact;
		ObjContact.ContactName = GetName();
		if (CheckExistingContact(ObjContact.ContactName))
		{
			cout << "\n\n\t\tContact Name Already Exists.\n\n\t\tDo you want to add a new contact number to the existing contact?";
			cout << "\n\n\t\ty = Yes add more numbers.\n\n\t\tn = No. Add as a new contact.\n\n\t\tEnter your choice: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				if (DisplaySpecificContacts(ObjContact.ContactName) > 1)
				{
					cout << "\n\n\t\b\b\b======================================================================";
					cout << "\n\n\t\tEnter the Existing Contact No of the Contact: ";
					PhoneNo = GetNo();
					for (Contact& ExistingContact : Contacts)
					{
						if (ExistingContact.ContactName == ObjContact.ContactName)
						{
							for (string No : ExistingContact.ContactNo)
							{
								if (No == PhoneNo)
								{
									cout << "\n\n\t\b\b\b======================================================================";
									cout << "\n\n\t\tEnter the New Contact No.:";
									PhoneNo = GetNo();
									ch = MergeContacts(PhoneNo);
									while (ch != 'n' && ch != 'N')
									{
										if (ch == 'y' || ch == 'Y')
										{
											ExistingContact.ContactNo.push_back(PhoneNo);
											cout << "\n\n\t\tDo you want to add more contact numbers to " << ObjContact.ContactName << "?";
											cout << "\n\n\t\ty = Yes & n = No\n\n\t\tEnter your choice: ";
											cin >> ch;
											if (ch == 'y' || ch == 'Y')
											{
												PhoneNo = GetNo();
											}
										}
									}
									ch = 'c';
									break;
								}
							}
						}
						if (ch == 'c')
						{
							break;
						}
					}
				}
				else
				{
					for (Contact& ExistingContact : Contacts)
					{
						if (ExistingContact.ContactName == ObjContact.ContactName)
						{
							cout << "\n\n\t\b\b\b======================================================================";
							cout << "\n\n\t\tEnter the New Contact No.:";
							PhoneNo = GetNo();
							ch = MergeContacts(PhoneNo);
							while (ch != 'n' && ch != 'N')
							{
								if (ch == 'y' || ch == 'Y')
								{
									ExistingContact.ContactNo.push_back(PhoneNo);
									cout << "\n\n\t\tDo you want to add more contact numbers to " << ObjContact.ContactName << "?";
									cout << "\n\n\t\ty = Yes & n = No\n\n\t\tEnter your choice: ";
									cin >> ch;
									if (ch == 'y' || ch == 'Y')
									{
										PhoneNo = GetNo();
									}
								}
							}
							ch = 'x';
							break;
						}
					}
				}
			}
			if (ch == 'n' || ch == 'N')
			{
				AddNewContact(AddContact);
				j++;
			}
		}
		else
		{
			AddNewContact(AddContact);
			j++;
		}
	}
	cout << "\n\n\t\t" << j << " Contacts Added.\n\n\t\t";
	j = 0;
}

void PhoneBookMethods::DisplayContacts() //Displaying Contacts
{
	cout << "\n\n\t\b\b======================================================================";
	cout << "\n\n\t\b\b~~~~~~~~~~~~~~~~~~~~~~~     CONTACT DETAILS     ~~~~~~~~~~~~~~~~~~~~~~";
	cout << "\n\n\t\b\b======================================================================";
	if (Contacts.empty())
	{
		cout << "\n\n\t\t\b\b\bNo Contacts in the phone book.";
	}
	else
	{
		cout << "\n\n\t\t\b\b\bThe details of " << Contacts.size() << " contacts are: \n";
		for (Contact& DisplayContacts : Contacts)
		{
			cout << "\n\n\t\t\b\b\bContact Name: " << DisplayContacts.ContactName;
			cout << "\n\n\t\t\b\b\bContact No(s): ";
			DisplayContacts.ContactNo.sort();
			DisplayContacts.ContactNo.unique();
			for (string N : DisplayContacts.ContactNo)
			{
				cout << N << " ";
			}
			cout << "\n";
		}
	}
}

void PhoneBookMethods::UpdateContact() //Updating Contacts
{
	char ch{ 'a' };
	int F = 1;
	while (ch != '3')
	{
		cout << "\n\n\t\b\b\b======================================================================";
		cout << "\n\n\t\b\b\b~~~~~~~~~~~~~~~~~~~~~~~~     UPDATE CONTACT    ~~~~~~~~~~~~~~~~~~~~~~~";
		cout << "\n\n\t\b\b\b======================================================================";
		cout << "\n\n\t\t\t      Choose an option:\n\n\t\t\t      1. Update Contact By Name\n\n\t\t\t      2. Update Contact By No.\n\n\t\t\t      3. Main Menu\n\n\t\t\t      Enter your choice: ";
		(cin >> ch).get();
		switch (ch)
		{
		case '1': //Update Contact By Name
			cout << "\n\n\t\tEnter the Contact Name to be updated: ";
			ObjContact.ContactName = GetName();
			if (DisplaySpecificContacts(ObjContact.ContactName) == 0)
			{
				system("cls");
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\t\b\b\bNo Contacts with " << ObjContact.ContactName << " availbale.";
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\t\b\b\b";
				system("pause");
			}
			system("cls");
			UpdateContactDetails(ObjContact.ContactName, ch);
			break;

		case '2'://Update Contact By No.
			cout << "\n\n\t\tEnter the Contact No to update contact: ";
			PhoneNo = GetNo();
			if (DisplaySpecificContacts(PhoneNo) == 0)
			{
				system("cls");
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\t\b\b\bNo Contacts with " << PhoneNo << " availbale.";
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\t\b\b\b";
				system("pause");
			}
			system("cls");
			UpdateContactDetails(PhoneNo, ch);
			break;

		case '3':
			break;


		default:
			cout << "\n\tPlease choose a correct option.\n";
			break;
		}
	}
}

void PhoneBookMethods::DeleteContact() //Deleting Contacts
{
	char ch{ 'a' };
	int F = 1;
	while (ch != '3')
	{
		cout << "\n\n\t\b\b\b======================================================================";
		cout << "\n\n\t\b\b\b~~~~~~~~~~~~~~~~~~~~~~~~     DELETE CONTACT    ~~~~~~~~~~~~~~~~~~~~~~~";
		cout << "\n\n\t\b\b\b======================================================================";
		cout << "\n\n\t\t\t      Choose an option:\n\n\t\t\t      1. Delete Contact by Name\n\n\t\t\t      2. Delete Contact by No.\n\n\t\t\t      3. Main Menu\n\n\t\t\t      Enter your choice: ";
		(cin >> ch).get();
		switch (ch)
		{
		case '1'://Delete Contact By Name
			cout << "\n\n\t\tEnter the Contact Name to be deleted: ";
			ObjContact.ContactName = GetName();
			if (DisplaySpecificContacts(ObjContact.ContactName) == 0)
			{
				system("cls");
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\t\b\b\bNo Contacts with " << ObjContact.ContactName << " availbale.";
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\t\b\b\b";
				system("pause");
			}
			system("cls");
			DeleteContactDetails(ObjContact.ContactName, ch);
			break;

		case '2'://Delete Contact By Contact No.
			cout << "\n\n\t\tEnter the Contact No to delete contact: ";
			PhoneNo = GetNo();
			if (DisplaySpecificContacts(PhoneNo) == 0)
			{
				system("cls");
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\t\b\b\bNo Contacts with " << PhoneNo << " availbale.";
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\t\b\b\b";
				system("pause");
			}
			system("cls");
			DeleteContactDetails(PhoneNo, ch);
			break;

		case '3':
			break;

		default:
			cout << "\n\tPlease choose a correct option.\n";
			break;
		}
	}
}

void PhoneBookMethods::SearchContact() // Searching Contacts
{
	char ch{ 'a' };
	while (ch != '3')
	{
		cout << "\n\n\t\b\b\b======================================================================";
		cout << "\n\n\t\b\b\b~~~~~~~~~~~~~~~~~~~         SEARCH CONTACT          ~~~~~~~~~~~~~~~~~~";
		cout << "\n\n\t\b\b\b======================================================================";
		cout << "\n\n\t\t\t      Choose an option:\n\n\t\t\t      1. Search Contact By Name\n\n\t\t\t      2. Search Contact By No.\n\n\t\t\t      3. Main Menu\n\n\t\t\t      Enter your choice: ";
		(cin >> ch).get();

		switch (ch)
		{
		case '1': //Search Contact By Name
			system("cls");
			cout << "\n\n\t\tEnter the Contact Name to be searched: ";
			getline(cin,ObjContact.ContactName);
			transform(ObjContact.ContactName.begin(), ObjContact.ContactName.end(), ObjContact.ContactName.begin(), toupper);
			if (DisplaySpecificContacts(ObjContact.ContactName) == 0)
			{
				if (system("cls") || SearchByName(ObjContact.ContactName) > 0)
				{
					cout << "\n\n\t\b\b\b======================================================================";
					cout << "\n\n\t\t";
					system("pause");
					system("cls");
				}
				else
				{
					system("cls");
					cout << "\n\n\t\t\b\b\bNo Contacts with " << ObjContact.ContactName << " availbale.";
				}
			}
			else if (DisplaySpecificContacts(ObjContact.ContactName) != 0)
			{
				system("cls");
				DisplaySpecificContacts(ObjContact.ContactName);
			}

			break;

		case '2'://Search Contact By No.
			system("cls");
			cout << "\n\n\t\tEnter the Contact No. to be searched: ";
			PhoneNo = GetNo();
			if (DisplaySpecificContacts(PhoneNo) == 0)
			{
				system("cls");
				cout << "\n\n\t\t\b\b\bNo Contacts with " << PhoneNo << " availbale.";
			}
			else if (DisplaySpecificContacts(ObjContact.ContactName) != 0)
			{
				system("cls");
				DisplaySpecificContacts(PhoneNo);
			}
			break;

		case '3':
			break;


		default:
			cout << "\n\tPlease choose a correct option.\n";
			break;
		}
	}
}






void PhoneBookMethods::AddNewContact(Contact& NewContact) //Add New Contacts
{
	char ch = 'a';
	NewContact.ContactName = ObjContact.ContactName;
	PhoneNo = GetNo();
	NewContact.ContactNo.push_back(PhoneNo);
	ch = MergeContacts(PhoneNo);
	if (ch == 'n')
	{
		j--;
	}
	else if (ch == 'y')
	{
		while (ch != 'n' && ch != 'N')
		{
			cout << "\n\n\t\tDo you want to add more contact numbers to " << NewContact.ContactName << "?";
			cout << "\n\n\t\ty = Yes & n = No\n\n\t\tEnter your choice: ";
			cin >> ch;
			if (ch == 'y' || ch == 'Y')
			{
				NewContact.ContactNo.push_back(GetNo());
			}
			if (ch == 'n' || ch == 'N')
			{
				Contacts.push_back(NewContact);
			}
		}
	}
}

int PhoneBookMethods::DisplaySpecificContacts(string Detail) //Display Specific Contacts
{
	int i = 0;
	cout << "\n\n\t\b\b\b======================================================================";
	cout << "\n\n\t\b\b\b~~~~~~~~~~~~~~~~~~~     DISPLAY SPECIFIC CONTACT    ~~~~~~~~~~~~~~~~~~";
	cout << "\n\n\t\b\b\b======================================================================";
	if (Detail.at(0) == '+')
	{
		cout << "\n\n\t\tThe Contact Details are: \n";
		for (Contact DisplayContact : Contacts)
		{
			for (string DisplayNo : DisplayContact.ContactNo)
			{
				if (DisplayNo == Detail)
				{
					cout << "\n\n\t\tContact Name: " << DisplayContact.ContactName << "\n";
					for (string DisplayNo : DisplayContact.ContactNo)
					{
						cout << "\n\t\tContact No(s): ";
						cout << DisplayNo << " ";
					}
					i++;
					cout << "\n\n";
				}
			}
		}
	}
	else
	{
		cout << "\n\n\t\tThe Contact Details are: \n";
		for (Contact DisplayContact : Contacts)
		{
			if (DisplayContact.ContactName == Detail)
			{
				cout << "\n\n\t\tContact Name: " << DisplayContact.ContactName << "\n";
				for (string DisplayNo : DisplayContact.ContactNo)
				{
					cout << "\n\t\tContact No(s): ";
					cout << DisplayNo << " ";
				}
				i++;
				cout << "\n\n";
			}
		}
	}
	return i;
}

void PhoneBookMethods::UpdateContactDetails(string Detail, char ch) // Update Contacts
{
	int F = 1;
	string Temp;
	if (DisplaySpecificContacts(Detail) > 1)
	{
		if (ch == '1')
		{
			cout << "\n\n\t\b\b\b======================================================================";
			cout << "\n\n\t\tEnter the Contact No. to Update Contact.";
			PhoneNo = GetNo();
			for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
			{
				if (It->ContactName == Detail)
				{
					for (string& TempNo : It->ContactNo)
					{
						if (TempNo == PhoneNo)
						{
							cout << "\n\n\t\b\b\b======================================================================";
							cout << "\n\n\t\tDo you want to Update Specific No. or Update Contact Name.";
							cout << "\n\n\t\ta. Update Contact No.\n\n\t\tb. Update Contact Name\n\n\t\tEnter your choice (a or b): ";
							cin >> ch;
							if (ch == 'a' || ch == 'A')
							{
								cout << "\n\n\t\tEnter the Updated Contact No.: ";
								Temp = GetNo();
								if (Temp == TempNo)
								{
									cout << "\n\n\t\tContact No. Not Updated.";
								}
								else
								{
									TempNo = Temp;
									cout << "\n\n\t\tContact No. Updated.";
								}
								F = 0;
								break;
							}
							else if (ch == 'b' || ch == 'B')
							{
								cout << "\n\n\t\b\b\b======================================================================";
								cout << "\n\n\t\tEnter the Updated Contact Name: ";
								ObjContact.ContactName = GetName();
								if (It->ContactName == ObjContact.ContactName)
								{
									cout << "\n\n\t\tContact Name Not Updated.";
								}
								else
								{
									It->ContactName = ObjContact.ContactName;
									cout << "\n\n\t\tContact Name Updated.";
								}
								F = 0;
								break;
							}
						}
					}
				}
				if (F == 0)
				{
					break;
				}
			}
		}

		if (ch == '2')
		{
			cout << "\n\n\t\b\b\b======================================================================";
			cout << "\n\n\t\tEnter the Contact Name to Delete Contact.";
			ObjContact.ContactName = GetName();
			for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
			{
				if (It->ContactName == ObjContact.ContactName)
				{
					for (string& TempNo : It->ContactNo)
					{
						if (TempNo == PhoneNo)
						{
							cout << "\n\n\t\b\b\b======================================================================";
							cout << "\n\n\t\tDo you want to Update Specific No. or Update Contact Name.";
							cout << "\n\n\t\ta. Update Contact No.\n\n\t\tb. Update Contact Name\n\n\t\tEnter your choice (a or b): ";
							cin >> ch;
							if (ch == 'a' || ch == 'A')
							{
								cout << "\n\n\t\tEnter the Updated Contact No.: ";
								Temp = GetNo();
								if (Temp == TempNo)
								{
									cout << "\n\n\t\tContact No. Not Updated.";
								}
								else
								{
									TempNo = Temp;
									cout << "\n\n\t\tContact No. Updated.";
								}
								F = 0;
								break;
							}
							else if (ch == 'b' || ch == 'B')
							{
								cout << "\n\n\t\b\b\b======================================================================";
								cout << "\n\n\t\tEnter the Updated Contact Name: ";
								ObjContact.ContactName = GetName();
								if (It->ContactName == ObjContact.ContactName)
								{
									cout << "\n\n\t\tContact Name Not Updated.";
								}
								else
								{
									It->ContactName = ObjContact.ContactName;
									cout << "\n\n\t\tContact Name Updated.";
								}
								F = 0;
								break;
							}
						}
					}
				}
				if (F == 0)
				{
					break;
				}
			}

		}
	}

	else if (system("cls") || DisplaySpecificContacts(Detail) == 1)
	{
		for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
		{
			if (ch == '1')
			{
				if (It->ContactName == Detail)
				{
					cout << "\n\n\t\b\b\b======================================================================";
					cout << "\n\n\t\tDo you want to Update Specific No. or Update Contact Name.";
					cout << "\n\n\t\ta. Update Contact No.\n\n\t\tb. Update Contact Name\n\n\t\tEnter your choice (a or b): ";
					cin >> ch;
					if (ch == 'a' || ch == 'A')
					{
						cout << "\n\n\t\tEnter the Contact No. to be update: ";
						PhoneNo = GetNo();
						for (string& TempNo : It->ContactNo)
						{
							if (TempNo == PhoneNo)
							{
								cout << "\n\n\t\tEnter the Updated Contact No.: ";
								Temp = GetNo();
								if (Temp == TempNo)
								{
									cout << "\n\n\t\tContact No. Not Updated.";
								}
								else
								{
									TempNo = Temp;
									cout << "\n\n\t\tContact No. Updated.";
								}
								F = 0;
								break;
							}
						}
					}
					else if (ch == 'b' || ch == 'B')
					{
						cout << "\n\n\t\b\b\b======================================================================";
						cout << "\n\n\t\tEnter the Updated Contact Name: ";
						ObjContact.ContactName = GetName();
						if (It->ContactName == ObjContact.ContactName)
						{
							cout << "\n\n\t\tContact Name Not Updated.";
						}
						else
						{
							It->ContactName = ObjContact.ContactName;
							cout << "\n\n\t\tContact Name Updated.";
						}
						F = 0;
						break;
					}
				}
			}

			if (ch == '2')
			{
				for (string& No : It->ContactNo)
				{
					if (No == Detail)
					{
						cout << "\n\n\t\b\b\b======================================================================";
						cout << "\n\n\t\tDo you want to Update Specific No. or Update Contact Name.";
						cout << "\n\n\t\ta. Update Contact No.\n\n\t\tb. Update Contact Name\n\n\t\tEnter your choice (a or b): ";
						cin >> ch;
						if (ch == 'a' || ch == 'A')
						{
							cout << "\n\n\t\tEnter the Contact No. to be update: ";
							PhoneNo = GetNo();
							for (string& No : It->ContactNo)
							{
								if (No == PhoneNo)
								{
									cout << "\n\n\t\tEnter the Updated Contact No.: ";
									Temp = GetNo();
									if (Temp == No)
									{
										cout << "\n\n\t\tContact No. Not Updated.";
									}
									else
									{
										No = Temp;
										cout << "\n\n\t\tContact No. Updated.";
									}
									F = 0;
									break;
								}
							}
						}
						else if (ch == 'b' || ch == 'B')
						{
							cout << "\n\n\t\b\b\b======================================================================";
							cout << "\n\n\t\tEnter the Updated Contact Name: ";
							ObjContact.ContactName = GetName();
							if (It->ContactName == ObjContact.ContactName)
							{
								cout << "\n\n\t\tContact Name Not Updated.";
							}
							else
							{
								It->ContactName = ObjContact.ContactName;
								cout << "\n\n\t\tContact Name Updated.";
							}
							F = 0;
							break;
						}
					}
				}
			}
			if (F == 0)
			{
				break;
			}
		}
	}
	else
	{
		system("cls");
	}

}

void PhoneBookMethods::DeleteContactDetails(string Detail, char ch) // Delete Contacts
{
	int F = 1;
	if (DisplaySpecificContacts(Detail) > 1)
	{
		if (ch == '1')
		{
			cout << "\n\n\t\b\b\b======================================================================";
			cout << "\n\n\t\tEnter the Contact No. to Delete Contact.";
			PhoneNo = GetNo();
			for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
			{
				if (It->ContactName == Detail)
				{
					for (string& TempNo : It->ContactNo)
					{
						if (TempNo == PhoneNo)
						{
							cout << "\n\n\t\tDo you want to Delete Specific No. or Complete Contact.";
							cout << "\n\n\t\ta. Delete Contact\n\n\t\tb. Delete Specific No.\n\n\t\tEnter your choice (a or b): ";
							cin >> ch;
							if (ch == 'a' || ch == 'A')
							{
								Contacts.erase(It);
								cout << "\n\n\t\tContact Deleted.";
								F = 0;
								break;
							}
							else if (ch == 'b' || ch == 'B')
							{
								if (It->ContactName == Detail && TempNo == PhoneNo)
								{
									It->ContactNo.remove(TempNo);
									cout << "\n\n\t\tContact No. Deleted.";
									F = 0;
									break;
								}
							}
						}
					}
				}
				if (F == 0)
				{
					break;
				}
			}
		}
		if (ch == '2')
		{
			cout << "\n\n\t\b\b\b======================================================================";
			cout << "\n\n\t\tEnter the Contact Name to Delete Contact.";
			ObjContact.ContactName = GetName();
			for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
			{
				if (It->ContactName == ObjContact.ContactName)
				{
					for (string& TempNo : It->ContactNo)
					{
						if (TempNo == PhoneNo)
						{
							cout << "\n\n\t\tDo you want to Delete Specific No. or Complete Contact.";
							cout << "\n\n\t\ta. Delete Contact\n\n\t\tb. Delete Specific No.\n\n\t\tEnter your choice (a or b): ";
							cin >> ch;
							if (ch == 'a' || ch == 'A')
							{
								Contacts.erase(It);
								cout << "\n\n\t\tContact Deleted.";
								F = 0;
								break;
							}
							else if (ch == 'b' || ch == 'B')
							{
								if (It->ContactName == Detail && TempNo == PhoneNo)
								{
									It->ContactNo.remove(TempNo);
									cout << "\n\n\t\tContact No. Deleted.";
									F = 0;
									break;
								}
							}
						}
					}
				}
				if (F == 0)
				{
					break;
				}
			}

		}
	}

	else if (system("cls") || DisplaySpecificContacts(Detail) == 1)
	{
		for (list<Contact>::iterator It = Contacts.begin(); It != Contacts.end(); It++)
		{
			if (ch == '1')
			{
				if (It->ContactName == Detail)
				{
					cout << "\n\n\t\b\b\b======================================================================";
					cout << "\n\n\t\tDo you want to Delete Specific No. or Complete Contact.";
					cout << "\n\n\t\ta. Delete Contact\n\n\t\tb. Delete Specific No.\n\n\t\tEnter your choice (a or b): ";
					cin >> ch;
					if (ch == 'a' || ch == 'A')
					{
						Contacts.erase(It);
						cout << "\n\n\t\tContact Deleted.";
						F = 0;
						break;
					}
					else if (ch == 'b' || ch == 'B')
					{
						cout << "\n\n\t\b\b\b======================================================================";
						cout << "\n\n\t\tEnter the Contact No. to be Deleted: ";
						PhoneNo = GetNo();
						for (string& TempNo : It->ContactNo)
						{
							if (TempNo == PhoneNo && It->ContactName == Detail)
							{
								It->ContactNo.remove(TempNo);
								cout << "\n\n\t\tContact No. Deleted.";
								F = 0;
								break;
							}
						}
						if (F == 1)
						{
							system("cls");
							cout << "\n\n\t\b\b\b======================================================================";
							cout << "\n\n\t\tContacts No. " << PhoneNo << " not availbale.";
						}
					}
				}
			}

			if (ch == '2')
			{
				for (string& No : It->ContactNo)
				{
					if (No == Detail)
					{
						cout << "\n\n\t\b\b\b======================================================================";
						cout << "\n\n\t\tDo you want to Delete Specific No. or Complete Contact.";
						cout << "\n\n\t\ta. Delete Contact\n\n\t\tb. Delete Specific No.\n\n\t\tEnter your choice (a or b): ";
						cin >> ch;
						if (ch == 'a' || ch == 'A')
						{
							Contacts.erase(It);
							cout << "\n\n\t\tContact Deleted.";
							F = 0;
							break;
						}
						else if (ch == 'b' || ch == 'B')
						{
							It->ContactNo.remove(No);
							cout << "\n\n\t\tContact No. Deleted.";
							F = 0;
							break;
						}
					}
				}
			}
			if (F == 0)
			{
				break;
			}
		}
	}
	else
	{
		system("cls");
	}
}




char PhoneBookMethods::MergeContacts(string PhoneNo) // Check to Merge Contacts
{
	char ch;
	for (Contact& MergeContact : Contacts)
	{
		for (string& MergeNo : MergeContact.ContactNo)
		{
			if (MergeNo == PhoneNo)
			{
				DisplaySpecificContacts(PhoneNo);
				cout << "\n\n\t\b\b\b======================================================================";
				cout << "\n\n\t\tContact with same Contact No. Already Exist.";
				cout << "\n\n\t\tDo you wish to merge it with existing contact?";
				cout << "\n\n\t\ty = Yes & n = No\n\n\t\tEnter your choice: ";
				cin >> ch;
				if (ch == 'y' || ch == 'Y')
				{
					return 'n';
				}
				else if (ch == 'n' || ch == 'N')
				{
					return 'y';
				}
			}
		}
	}
	return ch = 'y';
}

bool PhoneBookMethods::CheckExistingContact(string Name) // Check for Existing Contact Name
{
	for (Contact CheckContact : Contacts)
	{
		if (CheckContact.ContactName == Name)
		{
			return true;
		}
	}
	return false;
}

int PhoneBookMethods::SearchByName(string Detail) // Search By string
{
	cout << "\n\n\t\b\b\b======================================================================";
	cout << "\n\n\t\b\b\b~~~~~~~~~~~~~~~~~~~         SEARCH CONTACT          ~~~~~~~~~~~~~~~~~~";
	cout << "\n\n\t\b\b\b======================================================================";
	int Counter = 0;
	for (Contact SearchContact : Contacts)
	{
		//if (SearchContact.ContactName.substr(0, Detail.length()) == Detail)
		if(!SearchContact.ContactName.find(Detail))
		{
			cout << "\n\n\t\tContact Name: " << SearchContact.ContactName << "\n";
			for (string DisplayNo : SearchContact.ContactNo)
			{
				cout << "\n\t\tContact No(s): ";
				cout << DisplayNo << " ";
			}
			cout << "\n\n";
			Counter++;
		}
	}
	return Counter;
}




string GetRandomString() //Get Random Characters to Make String
{
	string s1, s2, s;
	for (int i = 1; i <= 10; i++)
	{
		while (s1.length() != 5)
		{
			char c = ((rand() % 26) + 65);
			s1 += c;
		}
		while (s2.length() != 2)
		{
			char c = ((rand() % 26) + 65);
			s2 += c;
		}
		s = s1 + " " + s2;
	}
	return s;
}

void PhoneBookMethods::FillPhoneBook() // Fill DB with Dummy Data
{
	for (int i = 1; i <= 5; i++)
	{
		Contact Temp;
		Temp.ContactName = GetRandomString();
		transform(Temp.ContactName.begin(), Temp.ContactName.end(), Temp.ContactName.begin(), toupper);
		do
		{
			PhoneNo += ((rand() % 4) + 49);
			if (PhoneNo.length() == 10)
			{
				Temp.ContactNo.push_back(PhoneNo);
				PhoneNo.clear();
			}
			if (Temp.ContactNo.size() > 2)
			{
				break;
			}
		} while (Temp.ContactNo.size() != ((rand() % 10) + 52));
		Contacts.push_back(Temp);
	}
}
