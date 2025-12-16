#ifndef HANDLEINPUT_H
#define HANDLEINPUT_H

#include "../model/window.h"
#include "../model/model.h"

void handleInput(int *ch, int *destLen, char destText[], InputType fieldType, int maxLen, mutationFunc func, InputField fields[], fetcherAdmin dataFetcher, windowModel *windowM);

#endif