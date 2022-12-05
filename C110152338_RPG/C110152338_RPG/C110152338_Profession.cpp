#include <string>
#include "C110152338_Profession.h"
using namespace std;

CProfession::CProfession() {
}

CProfession::~CProfession() {
}
void CProfession::set_job_num(int take) {
	job_num = take;
}
int CProfession::show_jub_num() {
	return job_num;
}
