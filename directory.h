#ifndef   DIRECTORY_H__
#define   DIRECTORY_H__
#include  <iostream>
#include  <vector>

using namespace std; 


bool    ScanDirectory( const string &src_dir_path,   const string &file_extension,  vector<string>& src_files );
void    ScanNSortImagesInDirectory ( string  src_dir,  vector<string> &vec_src_files );



void    getObjectFiles (const vector<string> &vec_src_files, string  newDirectory, string  fileExt,vector<string> &vec_kp_files);








#endif