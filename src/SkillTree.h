#ifndef TGM_SKILLTREE_H
#define TGM_SKILLTREE_H

#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <iostream>
#include <algorithm>

#include "olcPixelGameEngine.h"

class SkillTree {
public:
    void addNode(std::string title,
	    std::string flavourText,
	    std::string graphicPath,
	    int tier);

    void addDependency(std::string dependant, std::string dependency);
    bool isSkillComplete(std::string skill) const;
    void drawSelf(olc::PixelGameEngine *pge) const;
    void tick(olc::PixelGameEngine *pge);
private:
    class SkillTreeNode {
    public:
	SkillTreeNode() = default;
	SkillTreeNode(std::string title,
		std::string flavourText,
		std::string graphicPath,
		olc::vf2d pos);

	void addDependency(std::string dependency);
	void drawSelf(olc::PixelGameEngine *pge) const;
	void tick(olc::PixelGameEngine *pge, const SkillTree &skillTree);
	const std::vector<std::string> &getDependecies() const;
	olc::vf2d getPos() const;
	bool isCompleted() const;
	bool isCompletable(const SkillTree &skillTree) const;
	void complete();
    private:
	std::string title;
	std::string flavour;
	std::unique_ptr<olc::Renderable> graphic;
	std::vector<std::string> deps;
	olc::vf2d pos;
	bool completed = false;
    };

    std::unordered_map<std::string, SkillTreeNode> nodes;
    std::vector<int> tierCounts = std::vector<int>(10u, 0);
};

#endif
