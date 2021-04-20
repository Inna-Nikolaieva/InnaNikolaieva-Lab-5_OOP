/* 17. Створити базовий клас КВИТОК НА ПОЇЗД (задаються дані про пасажира, номер вагона).
Створити похідні класи КУПЕЙНИЙ КВИТОК (задаються номер місця в межах від 1 до 36, вартість) 
та КВИТОК-ЛЮКС (задаються номер місця в межах від 1 до 18, вартість). Для заданих прикладів квитків перевірити правильність введених даних 
(коректність номера місця), визначити тип місця в залежності від номера (верхнє або нижнє, ліве або праве) відсортувати за зростанням вартості і 
обчислити їх сумарну вартість. Для перевірки використати масив вказівників на об’єкти базового класу, яким присвоїти адреси об’єктів похідних класів.*/
#include <iostream>
#include <string>

#define KST 30

using namespace std;

class Train_Ticket					//базовий клас
{
protected:
	string data;					//дані про пасажира
	int number;						//номер вагона
public:
	Train_Ticket() { data = ""; number = 0; }
	Train_Ticket(string str, int n) : data(str), number(n) { }
	~Train_Ticket() {}

	string	get_data() { return data; }
	int get_number() { return number; }

	virtual int get_place() { return 0; }
	virtual void SetData() { return; }
	virtual double get_price() { return 0; }
	virtual void Typeofplace() { return; }
};

class Compartment_Ticket : public Train_Ticket
{
private:
	int place;						//місце у вагоні
	double price;					//вартість квитка
public:
	Compartment_Ticket() : Train_Ticket(), place(0), price(0) { }
	Compartment_Ticket(string str, int n, int p, double c) :Train_Ticket(str, n), place(p), price(c) {}
	~Compartment_Ticket() {}

	int get_place() { return place; }
	double get_price() { return price; }

	void SetData()
	{
		if (get_place() < 1 || get_place() > 36)
		{
			cout << "Incorrectly entered data!!!" << endl;
			system("pause");
			return;
		}
	}

	void Typeofplace()
	{
		if (get_place() % 2 == 0)
			cout << "Top shelf.";
		else
			cout << "Bottom shelf.";
	}
};

class Luxury_Ticket : public Train_Ticket
{
private:
	int place;						//місце у вагоні
	double price;					//вартість квитка
public:
	Luxury_Ticket() :Train_Ticket(), place(0), price(0) {}
	Luxury_Ticket(string str, int n, int p, double c) :Train_Ticket(str, n), place(p), price(c) {}
	~Luxury_Ticket() {}

	int get_place() { return place; }
	double get_price() { return price; }

	void SetData()
	{
		if (get_place() < 1 || get_place() > 18)
		{
			cout << "Incorrectly entered data!!!" << endl;
			system("pause");
			return;
		}
	}

	void Typeofplace()
	{
		if (get_place() % 2 == 0)
			cout << "Right place.";
		else
			cout << "Left place.";
	}
};

int input_data(Train_Ticket* p[]);
void sort(Train_Ticket* p[], int k);
void print(Train_Ticket* p[], int k);
double total_cost(Train_Ticket* p[], int k);

int main(void)
{
	Train_Ticket* p[KST];
	int kst = input_data(p);
	sort(p, kst);
	print(p, kst);
	double sum = total_cost(p, kst);
	cout << endl << "Total cost: " << sum << endl;
	system("pause");
	return 0;
}

int input_data(Train_Ticket* p[])
{
	int kst = 0;
	cout << "Enter the number of tickets: ";
	cin >> kst;
	for (int i = 0; i < kst; i++)
	{
		string n;
		int num = 0, pl = 0;
		double pr = 0;
		cout << endl << "Enter passenger data: ";
		cin >> n;
		cout << "Enter the train number: ";
		cin >> num;
		cout << "Enter the ticket type (c-Compartment Ticket, l-Luxury Ticket): ";
		char type;
		cin >> type;
		if (type == 'c')
		{
			cout << "Enter a place: ";
			cin >> pl;
			cout << "Enter the price: ";
			cin >> pr;
			p[i] = new Compartment_Ticket(n, num, pl, pr);
			p[i]->SetData();
		}
		if (type == 'l')
		{
			cout << "Enter a place: ";
			cin >> pl;
			cout << "Enter the price: ";
			cin >> pr;
			p[i] = new Luxury_Ticket(n, num, pl, pr);
			p[i]->SetData();
		}
	}
	return kst;
}

void sort(Train_Ticket* p[], int k)
{
	for (int i = 0; i < k; i++)
	{
		for (int j = i + 1; j < k; j++)
		{
			if ((*p[i]).get_price() > (*p[j]).get_price())
			{
				Train_Ticket* tmp = p[i];
				p[i] = p[j];
				p[j] = tmp;
			}
		}
	}
}

void print(Train_Ticket* p[], int k)
{
	cout << endl;
	for (int i = 0; i < k; i++) {
		cout << i + 1 << ". " << "Passenger data: " << p[i]->get_data() << "        ";
		cout << "Train number: " << p[i]->get_number() << "        ";
		cout << "Place: " << p[i]->get_place() << "        ";
		p[i]->Typeofplace(); cout << "        ";
		cout << "Price: " << p[i]->get_price() << endl;
	}
}

double total_cost(Train_Ticket* p[], int k)
{
	double sum = 0;
	for (int i = 0; i < k; i++)
		sum += p[i]->get_price();
	return sum;
}