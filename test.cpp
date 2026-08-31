//include 
#include <string>
#include <set>


class Message;
class Folder;


class Message
{
    friend class Folder;
    public:
        explicit Message(std::string s = std::string("")):contents(s){}
        Message(const Message& copy);
        Message& operator=(const Message& copy);
        ~Message();
        void Save(const Folder& );
        void Remove(const Folder& );

    private:
        std::string contents;
        std::set<Folder*> folder;

};


