#include <thread>//thread id
#include <cstring>//std::string

#include "logger.hpp"

using namespace ilrd;
using namespace std;

int main()
{
    ofstream myfile;
    myfile.open("a.log");
    Logger logger;
    logger.SetOutput(myfile);
    std::string s("hello world, nice to meet you");


    logger.Log(Logger::ERROR,
    std::this_thread::get_id(), 
                        "ERROR TYPE",
                        __FILE__ , __LINE__,  "Hello world, nice to meet you");
    logger.Log(Logger::WARNING,
    std::this_thread::get_id(),
                        "ERROR TYPE",
                        __FILE__, __LINE__,"mom look, im on tv");
/*     logger.Log(Logger::ERROR, "hi mom\n"); 
    logger.Log(Logger::INFO, "look mom no hands\n"); 
 
    ifstream tester;
    tester.open("a.log");
    string test;

    myfile.seekp(0);
    string results[6] = {"hi", "mom", "look", "mom"
            , "no", "hands"};
    int i =0;
    while(tester >> test)
    {
        if(test != results[i])
        {
            cout << " error: " << test;
        }
        ++i;
    } 

    logger.SetOutputSeverity(Logger::ERROR);
    logger.Log(Logger::INFO, "this should not be written"); 

    tester >> test;
    if( "hands" != test)
    {
        cout << "I was not supposed to output that!" << endl;
    }
    
    myfile.close();
    ofstream myfile2;
    myfile2.open("a.log2");
    fstream tester2;
    tester2.open("a.log2");
    logger.SetOutput(myfile2);

    logger.Log(Logger::ERROR, "now this on the other hand should output"); 
    string results2[8] = {"now","this","on","the","other",
                    "hand","should","output"};
    myfile2.seekp(0);
    i =0;

    while(tester2 >> test)
    {
        if(test != results2[i])
        {
            cout << " error: " << test;
        }
        ++i;
    } 
    logger.SetOutput(cerr);

    ofstream out("error_file_cerr.txt");
    streambuf *coutbuf = cerr.rdbuf();
    cerr.rdbuf(out.rdbuf());
    logger.Log(Logger::ERROR, "to the cerr, and beyond!");

    cerr.rdbuf(coutbuf);
    i =0;
    ifstream myfile3;
    myfile3.open("error_file_cerr.txt");
    fstream tester3;
    tester3.open("error_file_cerr.txt");
    string results3[5] = {"to","the","cerr,","and","beyond!"};
    string test3;

    while(tester3 >> test3)
    {
        if(test3 != results3[i])
        {
            cout << " error: " << test3;
        }
        ++i;
    }   */

    return 0;
}
