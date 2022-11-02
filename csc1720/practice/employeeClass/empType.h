class empType
{
   private:
		string name;
		int age;
		double salary;
	public:
		void setName(string empName);
		void getName(string& empName) const;
		void setAge(int empAge);
		void getAge(int& empAge) const;
		void setSalary(double empSalary);
		void getSalary(double empSalary) const;
		void empType(string empName, int empAge, double empSalary);
		void empType();
};
