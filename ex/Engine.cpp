#include"Engine.h"
/*#define show_engine(id) case id:{ifstream file("engine_" #id ".txt");   string s;  file>>s;  cout<<s;} */
Engine::Engine(){}
void Engine::show(int p)
{
        ostringstream os;
        os<<"engine_\\engine_"<<p<<".txt";
        string s=os.str();
        ifstream file(s.c_str());
        while(file)
        {
            getline(file,s);
            cout<<s<<endl;
        }
}
void Engine::set_argument(string lei)
{
    leixing=lei;
}

