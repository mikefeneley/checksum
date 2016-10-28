#ifndef checksum_data_h
#define checksum_data_h

#include <QString>
#include <string>
#include "md5.h"
#include "sha1.h"
#include "sha256.h"
#include "sha512.h"

typedef enum hash_algo {
    none = 0,
    Md5 = 1,
    Sha1 = 2,
    Sha256 = 3,
    Sha512 = 4,
} algo;


/*
 * Obkect holds the filename whose checksum we want to verify,
 * and the hex string of the checksum we want to verify against.
 *
 * Getter functions are used to obtain the checksum of filename
 * using that particular checksum algorithim.
 */
class checksum_data
{
    public:
		    checksum_data();
        void set_filename(QString filename);
        void set_checksum(QString checksum);
        QString compare_checksum(algo algorithim);

    private: 
      std::string get_md5();
      std::string get_sha1();
      std::string get_sha256();
      std::string get_sha512();

  	private:
      std::string filename;
  		std::string checksum;
};


#endif