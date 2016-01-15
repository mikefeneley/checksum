#include "checksum_data.h"

checksum_data::checksum_data()
{
	filename = "";
	checksum = "";
}

void checksum_data::set_filename(QString Qfilename)
{
	this->filename = Qfilename.toStdString();
}

void checksum_data::set_checksum(QString Qchecksum)
{
	this->checksum = Qchecksum.toStdString();
}

QString checksum_data::compare_checksum(algo algorithim)
{

	std::cout << filename << "\n";
	std::cout << checksum << "\n";
	QString return_msg;

	if(!algorithim) {
		return_msg = "Please specifiy which hash function to use";
	} else if (filename.empty()){
		return_msg = "Please select a file to check";
	} else {
		std::string checksum_result;
		if(algorithim == Md5) {
			checksum_result = get_md5();
		} else if (algorithim == Sha1) {
			checksum_result = get_sha1();
		} else if (algorithim == Sha256) {
			checksum_result = get_sha256();
		} else if (algorithim == Sha512) {
			checksum_result = get_sha512();
		} else {
			checksum_result = "Could not find hash function";
		}


		// Need to take case sensisittive into consideration
		if(checksum_result.compare(checksum) == 0) {
			return_msg == "Checksum is the same\n";
		} else {
			return_msg = QString::fromStdString(checksum_result);
		}




	}
	return return_msg;

}

std::string checksum_data::get_md5()
{
	MD5 md5;
  	FILE * file;
  	long size;
  	char * buffer;
  	size_t result;
  	
  	file = fopen (filename.c_str(), "rb" );
	fseek (file , 0 , SEEK_END);
	size = ftell (file);
  	rewind (file);

	buffer = (char*) malloc (sizeof(char)*size);
 	result = fread (buffer, 1, size, file);

	md5.update(buffer, result);
	md5.finalize();
	return md5.hexdigest();
}

std::string checksum_data::get_sha1()
{
	return "find sha1 implemented";
}

std::string checksum_data::get_sha256()
{
	return "find sha256 implemented";
}

std::string checksum_data::get_sha512()
{
	return "find sha512 implemented";
}