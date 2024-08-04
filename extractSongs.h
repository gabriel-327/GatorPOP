//
// Created by Shashank Navale on 8/3/24.
//

#ifndef GATORPOP_MAIN_EXTRACTSONGS_H
#define GATORPOP_MAIN_EXTRACTSONGS_H

#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

int dateFormatter(const string& dateString);
vector<pair<int, string> > extractTopSongs(string& filename);


#endif //GATORPOP_MAIN_EXTRACTSONGS_H
