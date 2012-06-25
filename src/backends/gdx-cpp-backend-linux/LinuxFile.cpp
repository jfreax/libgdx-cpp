#include "FileHandleStream.hpp"
#include <cstdio>
#include <cassert>
#include <gdx-cpp/implementation/System.hpp>
#include <gdx-cpp/Gdx.hpp>
#include <stdexcept>

using namespace gdx::files;

int File::getPrefixLength() const
{
    return prefixLength;
}

static bool initialized = false;

static void initializeFiles() {
    File::separatorChar = gdx::Gdx::system->getSeparator();
    File::separator = std::string("") + File::separatorChar;
    File::pathSeparatorChar = gdx::Gdx::system->getPathSeparator();
    File::pathSeparator = std::string("") + File::pathSeparatorChar;
}

char File::separatorChar;
std::string File::separator;
char File::pathSeparatorChar;
std::string File::pathSeparator;

File::File() 
  : path("")
{
    if (!initialized) {
        initializeFiles();
        initialized = true;
    }
}

File::File(const std::string& pathname, const int& prefixLength)
{
    if (!initialized) {
        initializeFiles();
        initialized = true;
    }
    this->path = pathname;
    this->prefixLength = prefixLength;
}

File::File(const std::string& child, const File &parent)
{
    if (!initialized) {
        initializeFiles();
        initialized = true;
    }
    assert(parent.path != "");
    this->path = gdx::Gdx::system->resolve(parent.path, child);
    this->prefixLength = parent.prefixLength;
}


File::File(const std::string& pathname)
{
    if (!initialized) {
        initializeFiles();
        initialized = true;
    }
    this->path = gdx::Gdx::system->normalize(pathname);
    this->prefixLength = gdx::Gdx::system->prefixLength(this->path);
}

File::File(const std::string& parent, const std::string& child)
{
    if (!initialized) {
        initializeFiles();
        initialized = true;
    }
    
    if(parent == "")
    {
        this->path = gdx::Gdx::system->resolve(gdx::Gdx::system->getDefaultParent(), gdx::Gdx::system->normalize(child));
    }
    else
    {
        this->path = gdx::Gdx::system->resolve(gdx::Gdx::system->normalize(parent), gdx::Gdx::system->normalize(child));
    }
    this->prefixLength = gdx::Gdx::system->prefixLength(this->path);
}

File::File(const File &parent, const std::string& child)
{
    if (!initialized) {
        initializeFiles();
        initialized = true;
    }
    
    if(parent.path == ""){
        this->path = gdx::Gdx::system->resolve(gdx::Gdx::system->getDefaultParent(), gdx::Gdx::system->normalize(child));
    }
    else{
        this->path = gdx::Gdx::system->resolve(parent.path, gdx::Gdx::system->normalize(child));
    }
    this->prefixLength = gdx::Gdx::system->prefixLength(this->path);
}

//File(URI uri);
//virtual File& operator=(const File& other);

std::string File::getName() const
{
    unsigned int index = path.rfind(separatorChar);
    if(index == path.npos || index < prefixLength) return path.substr(prefixLength);
    return path.substr(index + 1);
}

std::string File::getParent() const
{
    unsigned int index = path.rfind(separatorChar);
    if(index == path.npos) return "";   //O RETORNO EH GAMBS

    if (index < prefixLength){
        if ((prefixLength > 0) && (path.length() > prefixLength))
            return path.substr(0, prefixLength);
    }
    return path.substr(0, index);
}

File File::getParentFile() const
{
    std::string p = this->getParent();
    if(p == "") return File();
    return File(p, this->prefixLength);
}

const std::string &File::getPath() const
{
    return path;
}

bool File::isAbsolute() const
{
    return gdx::Gdx::system->isAbsolute(*this);
}

std::string File::getAbsolutePath() const
{
    return gdx::Gdx::system->resolve(*this);
}

File File::getAbsoluteFile() const
{
    std::string absPath = getAbsolutePath();
    return File(absPath, gdx::Gdx::system->prefixLength(absPath));
}

std::string File::getCanonicalPath() const //throws Runtime-Error
{
    std::string p = gdx::Gdx::system->resolve(*this);
    return gdx::Gdx::system->canonicalize(p);
}

File File::getCanonicalFile() const //throws Runtime-Error
{
    std::string canonPath = getCanonicalPath();
    int prefix = gdx::Gdx::system->prefixLength(canonPath);
    return File(canonPath, prefix);
}
//public URL(); throw MalformedURLException
//URI toURI()
//bool canRead();
//bool canWrite();

bool File::exists() const
{
    gdx::Gdx::system->checkRead(getAbsolutePath());
    return ((gdx::Gdx::system->getBooleanAttributes(*this) & gdx::Gdx::system->BA_EXISTS) != 0);
}

bool File::isDirectory() const
{
    gdx::Gdx::system->checkRead(getAbsolutePath());
    return ((gdx::Gdx::system->getBooleanAttributes(*this) & gdx::Gdx::system->BA_DIRECTORY) != 0);
}

//bool gotParent();

bool File::isFile() const
{
    gdx::Gdx::system->checkRead(getAbsolutePath());
    return ((gdx::Gdx::system->getBooleanAttributes(*this) & gdx::Gdx::system->BA_REGULAR) != 0);
}

//bool isHidden();
//int64_t lastModified();

int64_t File::length () const
{
    gdx::Gdx::system->checkRead(getCanonicalPath());  
    return gdx::Gdx::system->getLength(*this);
}

//bool createNewFile();  //throw IOException()

bool File::deleteFile()
{
    gdx::Gdx::system->checkDelete(getCanonicalPath());
    return gdx::Gdx::system->deleteFile(*this);
}

//void deleteOnExit();

void File::list(std::vector<std::string> &relativePaths)
{
    gdx::Gdx::system->checkRead(getCanonicalPath());
    gdx::Gdx::system->list(*this, relativePaths);
}

//void list(std::vector<std::string> &relativePath, FilenameFilter filter);

void File::listFiles(std::vector<File> &fileList)
{
    std::vector<std::string> ss;
    list(ss);
    int n = ss.size();
    fileList.resize(n);
    for(int i = 0; i<n; i++){
      fileList[i] = File(ss[i], *this);
    }
    return;
}

//void listFiles(std::vector<std::string> &relativePath, FilenameFilter filter);
//void listFiles(FileFilter filter);

bool File::mkdir()
{
    gdx::Gdx::system->checkWrite(getAbsolutePath());
    return gdx::Gdx::system->createDirectory(*this);
}

bool File::mkdirs()
{
    if(exists()) return false;
    if(mkdir()) return true;
    File canonFile;
    try{
        canonFile = getCanonicalFile();
    }
    catch (std::runtime_error e)
    {
        return false;
    }
    File parent = canonFile.getParentFile();
    return (parent.getPath() != "" && (parent.mkdirs() || parent.exists()) && canonFile.mkdir());
}

bool File::renameTo(const File &dest)   
{
    gdx::Gdx::system->checkWrite(getCanonicalPath());
    gdx::Gdx::system->checkWrite(dest.getAbsolutePath());
    if(gdx::Gdx::system->renameFile(*this, dest))
    {
        this->path = dest.getPath();
        this->prefixLength = dest.prefixLength;
        return true;
    }
    return false;
}

//bool setLastModified(int64_t &time);
//bool setReadOnly();
//bool setWritable(bool &writable, bool &ownerOnly);
//bool setWritable(bool &writable);
//bool setReadable(bool &readable, bool &ownerOnly);
//bool setReadable(bool &readable);
//bool setExecutable(bool &executable, bool &ownerOnly);
//bool setExecutable(bool &executable);
//bool canExecute();
//static void listRoots(std::vector<File> &list);
//int64_t getTotalSpace();
//int64_t getFreeSpace();
//int64_t getUsableSpace();
//static File createTempFile(const std::string &prefix, const std::string &suffix, const File &directory); //throws IOException
//static File createTempFile(const std::string &prefix, const std::string &suffix); //throws IOException
//int compareTo(const File &pathname);
//boolean equals(Object obj);
//int hashCode();

std::string File::toString()
{
    return getPath();
}



    //static std::string slashify(const std::string &path, const bool &isDirectory);
    /*
     * // lazy initialization of SecureRandom and temporary file directory
    private static class LazyInitialization {
        static final SecureRandom random = new SecureRandom();

        static final String temporaryDirectory = temporaryDirectory();
        static String temporaryDirectory() {
            return fs.normalize(
                AccessController.doPrivileged(
                    new GetPropertyAction("java.io.tmpdir")));
        }
    }
    */

//static File generateFile(const std::string &prefix, const std::string &suffix, const File &dir);
//static bool checkAndCreate(const std::string &filename, SecurityManager &sm);
//void writeObject(ObjectOutputStream s); //Throws IOException e syncronized
//void readObject(ObjectInputStream s); //Throws IOException e syncronized throws ClassNotFoundExceptionon

    /* treta loca no final do codigo
     *static {
        sun.misc.SharedSecrets.setJavaIODeleteOnExitAccess(
            new sun.misc.JavaIODeleteOnExitAccess() {
                public void run() {
                    DeleteOnExitHook.hook().run();
                }
            }
        );
    }
    */
