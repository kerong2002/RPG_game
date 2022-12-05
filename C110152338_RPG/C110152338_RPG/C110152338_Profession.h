#ifndef PROFESSION_H
#define PROFESSION_H

class CProfession{
	public:
		CProfession();
		~CProfession();
		void set_job_num(int);
		int show_jub_num();
	private:
		int job_num;
};

#endif