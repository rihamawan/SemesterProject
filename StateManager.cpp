// src/StateManager.cpp
#include "StateManager.h"
#include "GameEngine.h"
#include <fstream>
using namespace std;
StateManager::StateManager(const MyString& filePath): saveFilePath(filePath){}

void StateManager::save(const GameEngine& engine) {
    ofstream out(saveFilePath.returnArray(), ios::binary | ios::trunc);
    if (!out) {
        throw FileIOException(MyString("Cannot open save file: ").concat(saveFilePath));
    }

    // 1) Current level number
    int lvl = engine.getCurrentLevelNumber();
    out.write((const char*)&lvl, sizeof(lvl));

    // 2) Players
    const Dynamic_array<Player>& players = engine.getPlayers();
    int playerCount = players.size();
    out.write((const char*)&playerCount, sizeof(playerCount));


    for (const auto& p : players) {
        int len =MyString:: mystrlen(p.getName());
        out.write((const char*)&len, sizeof(len));
        out.write(p.getName().returnArray(), len);

        int score = p.getScore();
        out.write((const char*)&score, sizeof(score));

        float a = p.getAngle(), pw = p.getPower();
        out.write((const char*)&a, sizeof(a));
        out.write((const char*)&pw, sizeof(pw));
    }

    // 3) Targets’ destroyed flags
    const Dynamic_array<Target*>& targets = engine.getLevel().getTargets();
    int ts = targets.size();
    out.write((const char*)&ts, sizeof(ts));
    for (auto t : targets) {
        bool d = t->isDestroyed();
        out.write((const char*)&d, sizeof(d));
    }
}

void StateManager::load(const GameEngine& engine) {
    ifstream in(saveFilePath.returnArray(), ios::binary);
    if (!in) {
        throw FileIOException(MyString("Cannot open save file: ").concat(saveFilePath));
    }

    // 1) Level
    int lvl;
    in.read((char*)&lvl, sizeof(lvl));
    if (!in) throw ConfigParseException("Failed reading level number");
    engine.loadLevel(lvl);

    // 2) Players
    int ps;
    in.read((char*)&ps, sizeof(ps));
    if (!in) throw ConfigParseException("Failed reading player count");

    Dynamic_array<Player> players = engine.getPlayers();
    players.clear();
    for (int i = 0; i < ps; ++i) {
        int len;
        in.read((char*)&len, sizeof(len));
        if (!in) throw ConfigParseException("Failed reading name length");

        char* buffer = new char[len + 1];  
        in.read(buffer, len);
        if (!in) {
            delete[] buffer;
            throw ConfigParseException("Failed reading name");
        }
        buffer[len] = '\0';  

        MyString name(buffer);
        delete[] buffer;

        int score;
        in.read((char*)&score, sizeof(score));
        if (!in) throw ConfigParseException("Failed reading score");

        float angle, power;
        in.read((char*)&angle, sizeof(angle));
        in.read((char*)&power, sizeof(power));
        if (!in) throw ConfigParseException("Failed reading aim parameters");

        Player p(name, engine.getPlayerStartPosition(i));
        p.setAngle(angle);
        p.setPower(power);
        p.addScore(score);
        players.push(p);
    }

    // 3) Targets’ destroyed flags
    int ts;
    in.read((char*)&ts, sizeof(ts));
    if (!in) throw ConfigParseException("Failed reading target count");

    Dynamic_array<Target*> targets = engine.getLevel().getTargets();
    for (int i = 0; i < ts && i < targets.size(); ++i) {
        bool d;
        in.read((char*)&d, sizeof(d));
        if (!in) throw ConfigParseException("Failed reading target flag");
        targets[i]->setDestroyed(d);
    }
}
