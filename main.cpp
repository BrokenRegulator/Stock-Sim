#include <iostream>
#include <random>
#include <string>

using namespace std;

// Global Variables
int stockNum = 40;
int investorsNum = 3;
int user = 2;

// Lists
std::string rivals[4] = {"Dell", "Nvidia", "Microsoft", "Intel"};
std::string morale[5] = {"Dirt", "Bad", "Normal", "Good", "Space"};
std::string txtPunct[2][14] = {
    {"You have too little/many stocks in this company to sell/buy.", //[0][0]
     "You have $",                                                   //[0][1]
     "Your Company's Morale is ",                                    //[0][2]
     "Stock Price: ",                                                //[0][3]
     "Investors: ",                                                  //[0][4]
     "Morale Level: ",                                               //[0][5]
     "Do you want to buy? y/n",                                      //[0][6]
     "Investors or Stocks? i or s",                                  //[0][7]
     "What stocks do you want to buy? (0, 1, 2, 3)",                 //[0][8]
     "Do you want to sell? y/n",                                     //[0][9]
     "Investors or Stocks? i/s",                                     //[0][10]
     "What Stocks would you like to sell (0, 1, 2, 3)?",             //[0][11]
     "This is turn: ",                                               //[0][12]
     "Great Game! Your score is "},                                  //[0][13]
    {"", ". ", ".", "(", ")", ": ", "y", "i", "s", "___", "___", "___", "___",
     "___"} //[1][...]
};

// Choice
class choices {
public:
  int sell;
  int buy;
  string buy_y_n;
  string sell_y_n;
};

// Class For All Competitors
class CompetitorStatus {
public:
  int Stocks;
  int StocksNum;
  bool StockOwned;
  int Investors;
  std::string MoraleState;
};

// Class For Functions
class functions {
public:
  CompetitorStatus cs[4];
  choices Ch;
  int score;
  int userMor;
  int money;

  // Converter For Morale
  functions ConverterMor() {
    functions fun;
    for (int i = 0; i <= 3; i++) {
      if (cs[i].MoraleState == "Dirt") {
        cs[i].Stocks = cs[i].Stocks - 10;
      } else if (cs[i].MoraleState == "Bad") {
        cs[i].Stocks = cs[i].Stocks - 5;
      } else if (cs[i].MoraleState == "Normal") {
        cs[i].Stocks = cs[i].Stocks;
      } else if (cs[i].MoraleState == "Good") {
        cs[i].Stocks = cs[i].Stocks + 5;
      } else if (cs[i].MoraleState == "Space") {
        cs[i].Stocks = cs[i].Stocks + 10;
      }
      if (cs[i].Stocks < 0) {
        cs[i].Stocks = 0;
      } else if (cs[i].Stocks > 45) {
        cs[i].Stocks = 45;
      }
    }
    return fun;
  }

  // Zero Check
  std::string Zero() {
    for (int i = 0; i == Ch.sell; i++) {
      if (cs[i].StocksNum <= 0) {
        cs[i].StocksNum = 0;
      }
    }
    for (int i = 0; i == Ch.buy; i++) {
      if (cs[i].StocksNum >= 4) {
        cs[i].StocksNum = 4;
      }
    }
    return txtPunct[0][0];
  }

  // Check Owns Stocks
  std::string hasStocks() {
    for (int i = 0; i < 3; i++) {
      if (Ch.buy == i && cs[i].Stocks) {
        money = money - cs[i].Stocks;
        cs[i].StocksNum = cs[i].StocksNum + 1;
        cs[i].StockOwned = true;
        return "Owned";
      } else if (Ch.sell == i && cs[i].StocksNum > 1) {
        cs[i].StocksNum = cs[i].StocksNum - 1;
      } else if (Ch.sell == i && cs[i].StocksNum == 1) {
        cs[i].StockOwned = false;
        cs[i].StocksNum = cs[i].StocksNum - 1;
        return txtPunct[1][0];
      }
    }
    return "";
  }

  // Converter
  int Convert() {
    if (userMor == 0) {
      money = money - 32;
    } else if (userMor == 1) {
      money = money - 16;
    } else if (userMor == 3) {
      money = money + 14;
    } else if (userMor == 4) {
      money = money + 28;
    }
    return money;
  }

  // Calc Money
  int Calc() {
    money = money + (investorsNum * 3) + Convert();
    return money;
  }

  // Reset Choice Variables
  functions reset() {
    functions fun;
    fun.Ch.buy_y_n = txtPunct[1][0];
    fun.Ch.buy = 0;
    fun.Ch.sell_y_n = txtPunct[1][0];
    fun.Ch.sell = 0;
    return fun;
  }
};

// Competitors Init
functions initMarket(functions fun) {
  fun.score = 1;
  fun.userMor = user;
  fun.money = 25;
  for (int i = 0; i <= 3; i++) {
    fun.cs[i].Stocks = stockNum;
    fun.cs[i].StockOwned = false;
    fun.cs[i].Investors = investorsNum;
    fun.cs[i].MoraleState = morale[2];
    fun.cs[i].StocksNum = 0;
  }
  return fun;
}

// Display Stats
void display(functions fun) {
  cout << txtPunct[0][1] << fun.money << txtPunct[1][1] << txtPunct[0][2]
       << morale[fun.userMor] << txtPunct[1][2] << endl
       << endl;
  for (int i = 0; i <= 3; i++) {
    cout << i << txtPunct[1][5] << rivals[i] << endl;
    cout << txtPunct[0][3] << fun.cs[i].Stocks << txtPunct[1][3]
         << fun.cs[i].StockOwned << txtPunct[1][4] << endl;
    cout << txtPunct[0][4] << fun.cs[i].Investors << endl;
    cout << txtPunct[0][5] << fun.cs[i].MoraleState << endl << endl;
  }
}

// Random
functions RandomGenStocks(functions fun) {
  for (int i = 0; i <= 3; i++) {
    int begin = (rand() % 2);
    if (begin == 1) {
      fun.cs[i].Stocks = fun.cs[i].Stocks + (rand() % 10);
    } else {
      fun.cs[i].Stocks = fun.cs[i].Stocks - (rand() % 10);
    }
  }
  return fun;
}

// Choice Function
functions ChoiceFun(std::string buy_y_n, int buy, 
std::string sell_y_n, int sell) {
  functions fun;
  choices Ch;

  // Buying
  if (buy_y_n == txtPunct[1][0]) {
    cout << txtPunct[0][6] << endl;
    cin >> buy_y_n;
    // If Player inputs "y"
    if (buy_y_n == txtPunct[1][6]) {
      std::string buy_i_s = txtPunct[1][0];
      cout << txtPunct[0][7] << endl;
      cin >> buy_i_s;
      // If Player inputs "i"
      if (buy_i_s == txtPunct[1][7]) {
        investorsNum = investorsNum + 1;
        fun.money = fun.money - 15;
        // If Player inputs "s"
      } else if (buy_i_s == txtPunct[1][9]) {
        cout << txtPunct[0][8] << endl;
        cin >> buy;
        for (int i = 0; i == buy; i++) {
          fun.cs[i].StocksNum = fun.cs[i].StocksNum + 1;
        }
      }
    }
  }
  // Selling
  if (sell_y_n == txtPunct[1][0]) {
    cout << txtPunct[0][9] << endl;
    cin >> sell_y_n;
    // If Player inputs "y"
    if (sell_y_n == txtPunct[1][6]) {
      std::string sell_i_s = txtPunct[1][0];
      cout << txtPunct[0][10] << endl;
      cin >> sell_i_s;
      // If Player inputs "i"
      if (sell_i_s == txtPunct[1][7]) {
        investorsNum = investorsNum - 1;
        fun.money = fun.money + 15;
        // If Player inputs "s"
      } else if (sell_i_s == txtPunct[1][8]) {
        cout << txtPunct[0][11] << endl;
        cin >> sell;

        for (int i = 0; i == sell; i++) {
          fun.cs[i].StocksNum = fun.cs[i].StocksNum - 1;
        }
      }
    }
  }
  return fun;
}

// User Company Morale Random
functions convertRand(functions fun) {
  int userRand = (rand() % 2);
  if (userRand == 0) {
    fun.userMor = user + (rand() % 3);
  } else {
    fun.userMor = user - (rand() % 3);
  }
  fun.ConverterMor();
  fun.Convert();
  return fun;
}

int main() {
  functions fun;
  choices Ch;
  fun = initMarket(fun);
  // First Turn
  if (fun.score <= 1) {
    system("clear");
    cout << txtPunct[0][12] << fun.score << endl;
    convertRand(fun);
    fun.Calc();
    RandomGenStocks(fun);
    display(fun);
    fun = ChoiceFun(fun.Ch.buy_y_n, fun.Ch.buy, fun.Ch.sell_y_n, fun.Ch.sell);
    fun.score = fun.score + 1;
  }
  // Turns After
  while (fun.money >= 0 && fun.money < 175 && fun.score >= 1) {
    system("clear");
    if (fun.score >= 3) {
      fun.score = fun.score + 1;
    }
    cout << txtPunct[0][12] << fun.score << endl;
    if (fun.score % 2 == 0) {
      convertRand(fun);
      fun.Calc();
    }
    RandomGenStocks(fun);
    display(fun);
    fun.reset();
    fun = ChoiceFun(fun.Ch.buy_y_n, fun.Ch.buy, fun.Ch.sell_y_n, fun.Ch.sell);
    fun.Zero();
    return fun.score;
  }
  cout << txtPunct[1][13] << fun.score << endl;
  return 0;
}