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
    SkillTree(olc::PixelGameEngine *pge);
    void addNode(std::string title,
	    std::string flavourText,
	    std::string graphicPath,
	    int tier,
	    std::uint64_t cost);

    void addDependency(std::string dependant, std::string dependency);
    bool isSkillComplete(std::string skill) const;
    void drawSelf(olc::PixelGameEngine *pge, std::int64_t &internetPoints) const;
    bool tick(olc::PixelGameEngine *pge, std::int64_t &internetPoints);
private:
    class SkillTreeNode {
    public:
	SkillTreeNode() = default;
	SkillTreeNode(std::string title,
		std::string flavourText,
		std::string graphicPath,
		olc::vf2d pos,
		std::uint64_t cost);

	void addDependency(std::string dependency);
	void drawSelf(olc::PixelGameEngine *pge) const;
	void drawExplanation(olc::PixelGameEngine *pge, std::int64_t &internetPoints) const;
	bool tick(olc::PixelGameEngine *pge, const SkillTree &skillTree, std::int64_t &internetPoints);
	const std::vector<std::string> &getDependecies() const;
	olc::vf2d getPos() const;
	bool isCompleted() const;
	bool isCompletable(const SkillTree &skillTree) const;
	void complete();
    private:
	std::string title;
	std::string flavour;
	olc::Renderable graphic;
	std::vector<std::string> deps;
	olc::vf2d pos;
	bool completed = false;
	std::uint64_t cost;
    };

    std::unordered_map<std::string, SkillTreeNode> nodes;
    std::vector<int> tierCounts = std::vector<int>(10u, 0);
    friend class SkillTreeNode;
};

#endif
