#include "checksum_data.h"

#include "stdio.h"

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
	std::transform(checksum.begin(), checksum.end(), 
						checksum.begin(), ::tolower);

}

QString checksum_data::compare_checksum(algo algorithim)
{

	std::cout << filename << "\n";
	std::cout << checksum << "\n";
	std::string return_msg;

	if(!algorithim) {
		return_msg = "Please specifiy which checksum function to use";
	} else if (filename.empty()){
		return_msg = "Please select a file to check";
	} else {
		std::string checksum_function;
		std::string checksum_result;
		if(algorithim == Md5) {
			checksum_function = "Checksum function: MD5\n\n";
			checksum_result = get_md5();
		} else if (algorithim == Sha1) {
			checksum_function = "Checksum function: SHA1\n\n";
			checksum_result = get_sha1();
		} else if (algorithim == Sha256) {
			checksum_function = "Checksum function: SHA256\n\n";
			checksum_result = get_sha256();
		} else if (algorithim == Sha512) {
			checksum_function = "Checksum function: SHA512\n\n";
			checksum_result = get_sha512();
		} else {
			return "Could not calculate checksum";
		}

		std::string result;
		if(checksum_result.compare(checksum) == 0) {
			result = "Checksums are equal\n";
		} else {
			result = "Checksums are not equal\n";
		}

		std::string file_line = "File: " + filename + "\n";
		std::string file_checksum = "File checksum: " + checksum_result + "\n\n";
		std::string text_checksum = "Textfield checksum: \n" + checksum + "\n\n";
		return_msg = file_line + checksum_function + file_checksum 
							+ text_checksum + result;
	}
	return QString::fromStdString(return_msg);

}


/*
 * Note: Check Zedwood for SHA 1
 		 Seperate file conversion into its own file.
 		 Free data.
 */

std::string checksum_data::get_md5()
{
	MD5 md5;
  	FILE * file;
  	long size;
  	char * buffer;
  	size_t result;
  	std::string hexdigest;
  	
  	file = fopen (filename.c_str(), "rb" );
	fseek (file , 0 , SEEK_END);
	size = ftell (file);
  	rewind (file);

	buffer = (char*) malloc (sizeof(char)*size);
 	result = fread (buffer, 1, size, file);

	md5.update(buffer, result);
	md5.finalize();
	hexdigest = "\n" + md5.hexdigest();
	return hexdigest;
}


std::string checksum_data::get_sha1()
{

  	FILE * file;
  	long size;
  	char * buffer;
  	size_t result;
  	unsigned char hash[20];
	char hexstring[41];

  	file = fopen (filename.c_str(), "rb" );
	fseek (file , 0 , SEEK_END);
	size = ftell (file);
  	rewind (file);
	buffer = (char*) malloc (sizeof(char)*size);
 	result = fread (buffer, 1, size, file);


	sha1::calc(file, size, hash);
	sha1::toHexString(hash, hexstring);
	std::string hexdigest(hexstring);
 	return hexdigest;
}

std::string checksum_data::get_sha256()
{
	SHA256 sha256 = SHA256();
	sha256.init();
	FILE * file;
  	long size;
  	char * buffer;
  	size_t result;

  	file = fopen (filename.c_str(), "rb" );
	fseek (file , 0 , SEEK_END);
	size = ftell (file);
  	rewind (file);
    unsigned char digest[SHA256::DIGEST_SIZE];

	buffer = (char*) malloc (sizeof(char)*size);
 	result = fread (buffer, 1, size, file);
 	sha256.update((unsigned char *)buffer, result);
 	sha256.final(digest);

    char buf[2*SHA256::DIGEST_SIZE+1];
    buf[2*SHA256::DIGEST_SIZE] = 0;
    for (int i = 0; i < SHA256::DIGEST_SIZE; i++)
        sprintf(buf+i*2, "%02x", digest[i]);
    std::string hexdigest(buf);

 	return hexdigest;

}

std::string checksum_data::get_sha512()
{
	SHA512 sha512 = SHA512();
	sha512.init();
	FILE * file;
  	long size;
  	char * buffer;
  	size_t result;

  	file = fopen (filename.c_str(), "rb" );
	fseek (file , 0 , SEEK_END);
	size = ftell (file);
  	rewind (file);
    unsigned char digest[SHA512::DIGEST_SIZE];

	buffer = (char*) malloc (sizeof(char)*size);
 	result = fread (buffer, 1, size, file);
 	sha512.update((unsigned char *)buffer, result);
 	sha512.final(digest);

    char buf[2*SHA512::DIGEST_SIZE+1];
    buf[2*SHA512::DIGEST_SIZE] = 0;
    for (int i = 0; i < SHA512::DIGEST_SIZE; i++)
        sprintf(buf+i*2, "%02x", digest[i]);
    std::string hexdigest(buf);

 	return hexdigest;
 }