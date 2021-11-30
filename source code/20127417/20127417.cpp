#include<iostream>
#include<vector>
#include<sstream>
#include<string>
#include<fstream>
#include <algorithm>

using namespace std;
class categories
{
private:
	string ID;
	string Name;
public:

	categories()
	{
		ID = "";
		Name = "";
	}

	categories(string id, string name)
	{
		ID = id;
		Name = name;
	}

	void readFile(vector<categories> &C)
	{
		ifstream ifs;
		ifs.open("categories.txt");
		if (!ifs)
		{
			cerr << " can't open file.\n";
			exit(1);
		}
		while (!ifs.eof())
		{
			string temp;
			string id, name;
			getline(ifs, temp);
			stringstream ss(temp);
			getline(ss, temp, '=');
			getline(ss, temp, ',');
			id = temp;
			getline(ss, temp, '=');
			getline(ss, temp);
			name = temp;
			categories c(id, name);
			C.push_back(c);
		}
		ifs.close();
	}

	void PrintFile(vector<categories>C)
	{
		string s_cate = "Category: ";
		string s_id = "ID= ";
		string s_name = ", Name=";
		for (int i = 0; i < C.size(); i++)
		{
			cout << s_cate << s_id << C[i].ID << s_name << C[i].Name << "\n";
		}
	}

	void print_name_cate(vector<categories>C, string id)
	{
		for (int i = 0; i < C.size(); i++)
		{
			if (id == C[i].ID)
			{
				cout << C[i].Name;
			}
		}
	}
};


class products
{
private:
	string ID;
	string Name;
	string Price;
	string CategoryID;
public:

	products()
	{
		ID = "";
		Name = "";
		Price = "";
		CategoryID = "";
	}

	products(string id, string name, string price, string categoryID)
	{
		ID = id;
		Name = name;
		Price = price;
		CategoryID = categoryID;
	}

	void Read_file(vector<products>& P)
	{
		ifstream ifs;
		ifs.open("products.txt");
		if (!ifs)
		{
			cerr << " can't open file.\n";
			exit(1);
		}
		while (!ifs.eof())
		{
			string temp, id, name, price, categoryID;
			getline(ifs, temp);
			stringstream ss(temp);
			getline(ss, temp, '=');
			getline(ss, temp, ',');
			id = temp;
			getline(ss, temp, '=');
			getline(ss, temp, ',');
			name = temp;
			getline(ss, temp, '=');
			getline(ss, temp, ',');
			price = temp;
			getline(ss, temp, '=');
			getline(ss, temp);
			categoryID = temp;
			products p(id, name, price, categoryID);
			P.push_back(p);
		}
		ifs.close();
	}

	void Print_File(vector<products> P, string find_id)
	{
		for (int i = 0; i < P.size(); i++)
		{
			if (P[i].CategoryID == find_id)
			{
				cout << "Product: ID=" << P[i].ID << ", Name=" << P[i].Name << ", Price=" << P[i].Price << ", CategoryID=" << P[i].CategoryID << "\n";
			}
		}
	}

	bool checkFindName(string name1, string name2)
	{
		
		transform(name1.begin(), name1.end(), name1.begin(), ::toupper);
		transform(name2.begin(), name2.end(), name2.begin(), ::toupper);

		if (strstr(name1.c_str(), name2.c_str()))
			return true;
		else return false;
	}

	void print_from_name(string name, vector<products>p, vector< categories>c)
	{
		categories C;
		for (int i = 0; i < p.size(); i++)
		{
			if (checkFindName(p[i].Name, name) == true)
			{
				cout << p[i].CategoryID << ". Category: ";
				C.print_name_cate(c, p[i].CategoryID);
				cout << ", ID: " << p[i].ID << ", Name: " << p[i].Name << ", Price: " << p[i].Price << "\n";
			}
		}
	}

	string StringtoValue(string value)   // 1.000.000 => 1000000
	{
		stringstream line(value);
		string curr;
		string result;
		while (!line.eof())
		{
			getline(line, curr, '.');
			result = result + curr;
		}
		return result;

	}

	void print_from_price(string a, string b, vector<products>p, vector <categories> c)
	{
		categories C;
		string temp = StringtoValue(a);
		long long A = stoll(temp);
		temp= StringtoValue(b);
		long long B = stoll(temp);

		for (int i = 0; i < p.size(); i++)
		{
			string temp = StringtoValue(p[i].Price);
			long long price = stoll(temp);
			if (price >= A && price <= B)
			{

				cout << p[i].CategoryID << ". Category: ";
				C.print_name_cate(c, p[i].CategoryID);
				cout << ", ID: " << p[i].ID << ", Name: " << p[i].Name << ", Price: " << p[i].Price << "\n";
			}
			
		}
	}
	
};


void menu()
{
	int choose=0;
	categories C;
	products P;
	vector<categories>c;
	vector <products> p;
	C.readFile(c);
	P.Read_file(p);
	do
	{
		cout << "What do you want to do? \n1. Display all categories\n2. Find products by name\n3. Find products by price range\n\n0. Quit\n";
		cout << " please enter your choice: ";
		cin >> choose;
		if (choose == 1)
		{
			C.PrintFile(c);
			string ID_cate;
			cout << " please enter ID category: ";
			cin.ignore();
			getline(cin, ID_cate);
			P.Print_File(p, ID_cate);
		}
		if (choose == 2)
		{
			string name_find;
			cin.ignore();
			cout << " please enter name:";
			getline(cin, name_find);
			P.print_from_name(name_find, p, c);
		}
		
		if (choose == 3)
		{
			string a, b;
			cin.ignore();
			cout << " please enter [A,B]: A= ";
			getline(cin, a);
			cout << " B= ";
			getline(cin, b);
			P.print_from_price(a, b, p, c);

		}

	} while (choose != 0);
	cout << " \nThank youu!!\n";

}

int main()
{
                                     
	menu();
	return 0;
}
