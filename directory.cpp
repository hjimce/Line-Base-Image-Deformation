#include "directory.h"
#include  <io.h>
#include  <stdio.h>
#include  <stdlib.h>



#include <opencv2/photo.hpp>
#include <string.h>

 
//bool   ScanDirectory( const string &src_dir_path,   const string &file_extension,  vector<string>& src_files );

static int str_compare( const void *arg1, const void *arg2 )
{
    return strcmp ( ( * ( std::string* ) arg1 ).c_str (), 
                    ( * ( std::string* ) arg2 ).c_str () );
}


void    getObjectFiles (const vector<string> &vec_src_files, string  newDirectory,string  fileExt, vector<string> &vec_kp_files)
{

	char   fileName[256],fileDir[256];
	char   *ptemp;
	for(int i=0;i<vec_src_files.size();i++)
	{
		memset(fileName,0,sizeof(fileName));  memset(fileDir,0,sizeof(fileDir));

		strcpy(fileDir,newDirectory.c_str());

		strcpy(fileName,vec_src_files[i].c_str());
		ptemp = strrchr(fileName,'\.');
		 
		if(NULL!=ptemp)
		{
				
			*ptemp = 0;				
			strcat(fileName,fileExt.c_str());				
		}

		ptemp = strrchr(fileName,'\\');
		if(NULL!=ptemp)
		{			 	
			strcat(fileDir,ptemp);
			vec_kp_files.push_back(fileDir);	
		}
		else
		{
			vec_kp_files.push_back(vec_src_files[i]);
		}
		 
	}
	 

}

void    ScanNSortImagesInDirectory ( string  src_dir, vector<string> &vec_src_files )
{
	 
    vector< vector<string> > imgs;
	 
    imgs.resize(14);
	 
    for(unsigned int i = 0; i < imgs.size(); i++)
    {
        imgs[i].resize(0);
		 
    }

    string tempp = src_dir;

    ScanDirectory( tempp,  ".jpg", imgs[0]);
    ScanDirectory( tempp,  ".bmp", imgs[1]);
    ScanDirectory( tempp,  ".ppm", imgs[2]);
    ScanDirectory( tempp,  ".pgm", imgs[3]);
    ScanDirectory( tempp,  ".png", imgs[4]);
    ScanDirectory( tempp,  ".gif", imgs[5]);
    ScanDirectory( tempp,  ".tif", imgs[6]);

	ScanDirectory( tempp,  ".JPG", imgs[7]);
    ScanDirectory( tempp,  ".BMP", imgs[8]);
    ScanDirectory( tempp,  ".PPM", imgs[9]);
    ScanDirectory( tempp,  ".PGM", imgs[10]);
    ScanDirectory( tempp,  ".PNG", imgs[11]);
    ScanDirectory( tempp,  ".GIF", imgs[12]);
    ScanDirectory( tempp,  ".TIF", imgs[13]);

	char *temp;
	char  filename[256];
    for(unsigned int i = 0; i < imgs.size(); i++)
    {
        for(unsigned int j = 0; j < imgs[i].size(); j++)
        {
            vec_src_files.push_back(imgs[i][j]);
        }
    }

    // sort the filenames
    if(vec_src_files.size() > 0)
    {
        qsort( (void *)&(vec_src_files[0]),
            (size_t)vec_src_files.size(),
            sizeof(string),
            str_compare );
    }

 

}

bool  isDirectory(const string& fdname)
{
	_finddata_t fileInfo;

	if(-1!=_findfirst(fdname.c_str(), &fileInfo))
	{
		if ((fileInfo.attrib & _A_SUBDIR) )
		{
			return true;
		}

	}

	 
	return false; 
}




 

const string getFileType( const string &filename )
{
	// find the last character '.' of the filename
	string::size_type pos = filename.find_last_of( '.' );

	if ( pos != string::npos )
	{
		// return the last several characters including '.'
		return string( filename, pos, string::npos );
	}
	else
	{
		// return null string
		return "";
	}
}

 

bool   ScanDirectory(  const string &src_dir_path,const 
                            const string &file_extension,
                            vector<string>& src_files)  
{
	if (-1==_access( src_dir_path.c_str() ,0) )
    {
        return false;
    }

	_finddata_t fileInfo;
	intptr_t hFile;

	string dirName_filter = src_dir_path + string("\\") + string("*.*");

	if ( ( hFile = _findfirst( dirName_filter.c_str(), &fileInfo ) ) != -1 )
	{
		do
		{
		   // check whether it's a directory or a file
           if ( !(fileInfo.attrib & _A_SUBDIR) )
		   {
			   // it's a file, deel with the file
			   // check the file type, and deel with this file
			   if ( file_extension == string(".*") || getFileType(fileInfo.name)== file_extension )
			   {
				   string filename = src_dir_path + string("\\") + string(fileInfo.name);
				   src_files.push_back(filename);

				  
				   
			   }
		   }
		  
		} while (_findnext(hFile,&fileInfo) == 0);
		_findclose(hFile);
	}  
    return true;
}
