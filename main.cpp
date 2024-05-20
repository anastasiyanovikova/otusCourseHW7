#include <iostream>
#include <vector>
#include<fstream>
#include<string>
#include<chrono>
#include<time.h>
#include <iomanip>
#include <ctime>
#include <sstream>

bool saveBlock (std::vector<std::string> commands, std::string fileName)
{
  std::ofstream file (fileName + ".log");
  if (file.is_open ())
  {
    file << "bulk: ";
    std::cout << "bulk: ";
    for (auto it : commands)
    {
      std::cout << it << ", ";
      file << it << ", ";
    }
    
  std::cout << std::endl;
  }
  file.close ();
  return true;
}

bool bulk (long N)
{
  std::vector<std::string > commands;
  std::string firctCommandDate;
  int startBlockAmount = 0;
  int endBlockAmmount = 0;

  std::string curCom;
  std::string firstTime = "";
  while (std::getline (std::cin, curCom))
  {
    if (curCom.compare ("{") == 0)
    {
      if (startBlockAmount == 0 && commands.size() > 0)
      {
        saveBlock (commands, firstTime);
        commands.clear ();
      }
      startBlockAmount++;
    }
    else if (curCom.compare ("}") == 0)
    {
      if (startBlockAmount > 0)
      {
        endBlockAmmount++;
        if (endBlockAmmount == startBlockAmount)
        {
          saveBlock (commands, firstTime);
          commands.clear ();
          startBlockAmount = 0;
          endBlockAmmount = 0;
        }
      }
    }
    else
    {
      if (commands.size () == 0)
      {
        time_t rawtime;
        struct tm timeinfo;
        time (&rawtime);
        #ifdef __unix__
          localtime_r (&rawtime, &timeinfo); 
        #else
          localtime_s(&timeinfo, &rawtime);
        #endif

        std::ostringstream oss;
        oss << std::put_time (&timeinfo, "%d%m%Y%H%M%S");
        firstTime = oss.str ();
      }
      commands.push_back (curCom);

    }

    if (startBlockAmount == 0 && long(commands.size ()) == N)
    {
      saveBlock (commands, firstTime);
      commands.clear ();
    }
  }
    
  if (startBlockAmount == 0)
  {
    saveBlock (commands, firstTime);
    commands.clear ();
  }
    
  return true;
}

int main(int argc, char const *argv[])
{
  long N = 3;
  if(argc > 1)
    N = atoi (argv [1]);

  bulk (N);
}
