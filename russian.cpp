// You are playing Russian Roulette with a friend and
// a N chamber gun with n bullets in it. Your friend fires and 'click' it's an empty chamber. If you now fire, what is your chance of getting another empty chamber?

#include<iostream>
#include<set>
#include<numeric>
#include<vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


using namespace std;


class Gun
{
private:
   int mBullets;
   int mChambers;
   set<int> mLoadedChambers;

public: Gun(int bullets, int chambers)
      {
         mBullets = bullets;
         mChambers = chambers;
         LoadGun();
      }

private: void LoadGun()
      {
         while(mBullets > 0)
         {
            int chamber = rand() % mChambers + 1;
            if (mLoadedChambers.find(chamber) == mLoadedChambers.end())
            {
               mLoadedChambers.insert(chamber);
               mBullets--;
            }
         }
      }

public: int PullTrigger()
      {
         while(1)        // keep guessing until empty chamber found
         {
            int chamber = rand() % mChambers + 1;
            if (mLoadedChambers.find(chamber) == mLoadedChambers.end())
            {
               return mLoadedChambers.find(chamber % mChambers + 1) == mLoadedChambers.end() ? 1 : 0;    // is next chamber empty?
            }
         }
      }
};

int main()
{
   srand(time(NULL));

   int nBullets = 5;
   int nChambers = 73;
   int numGuns = 1000;
   int numTrials = 1000;

   vector<int> results;
   for (int i = 0; i < numGuns; ++i)
   {
      Gun* currGun = new Gun(nBullets, nChambers);
      for (int j = 0; j < numTrials; ++j)
      {
         results.push_back(currGun->PullTrigger());
      }
      delete currGun;
   }

   cout << "Average probability to survive is " << 1.0*accumulate(results.begin(), results.end(), 0) / results.size();
   
   return 0;
}
