class natGeoType
{
	private:
		string cover;
		int month, year;
		int issuesSold;
	public:
		void setCover(string);
		void setMonth(int);
		void setYear(int);
		void setIssuesSold(int);
		string getCover() const;
		int getMonth() const;
		int getYear() const;
		int getIssuesSold() const;

};
