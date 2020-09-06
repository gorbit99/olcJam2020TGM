#include "SkillTree.h"

SkillTree::SkillTree(olc::PixelGameEngine *pge) {
}

void SkillTree::addNode(std::string title,
	std::string flavourText,
	std::string graphicPath,
	int tier,
	std::uint64_t cost) {
    nodes[title] = std::move(SkillTreeNode{
	    title,
	    flavourText,
	    graphicPath,
	    {float(tier), float(tierCounts[tier])},
	    cost
	    });
    tierCounts[tier]++;
}

void SkillTree::addDependency(std::string dependant, std::string dependency) {
    nodes[dependant].addDependency(dependency);
}

bool SkillTree::isSkillComplete(std::string skill) const {
    return nodes.at(skill).isCompleted();
}

void SkillTree::drawSelf(olc::PixelGameEngine *pge, std::int64_t &internetPoints) const {
    for (auto &node : nodes) {
	node.second.drawSelf(pge);
	for (const auto &dependency : node.second.getDependecies()) {
	    const auto &depNode = nodes.at(dependency);
	    const auto posFrom = depNode.getPos() * 16 + olc::vi2d{4, 4};
	    const auto posTo = node.second.getPos() * 16 + olc::vi2d{4, 4};
	    const auto color = depNode.isCompleted() ? olc::GREEN : olc::RED;
	    pge->DrawLine(posFrom + olc::vf2d{80, 180}, posTo + olc::vf2d{80, 180}, color);
	}
    }
    for (auto &node : nodes) {
	node.second.drawExplanation(pge, internetPoints);
    }
}

bool SkillTree::tick(olc::PixelGameEngine *pge, std::int64_t &internetPoints) {
    bool completedOne = false;
    for (auto &node : nodes) {
	if (node.second.tick(pge, *this, internetPoints)) {
	    completedOne = true;
	}
    }
    return completedOne;
}

SkillTree::SkillTreeNode::SkillTreeNode(std::string title,
	std::string flavourText,
	std::string graphicPath,
	olc::vf2d pos,
	std::uint64_t cost)
    : title{title}, flavour{flavourText}, pos{pos}, cost{cost}
{
    graphic.Load(graphicPath);
}

void SkillTree::SkillTreeNode::addDependency(std::string dependency) {
    deps.push_back(dependency);
}

void SkillTree::SkillTreeNode::drawSelf(olc::PixelGameEngine *pge) const {
    pge->DrawDecal(pos * 16 + olc::vf2d{80, 180}, graphic);
}

void SkillTree::SkillTreeNode::drawExplanation(olc::PixelGameEngine *pge, std::int64_t &internetPoints) const {
    const auto mousePos = pge->GetMousePos();
    if (mousePos.x >= pos.x * 16 + 80 && mousePos.x <= pos.x * 16 + 88 &&
		mousePos.y >= pos.y * 16 + 180 && mousePos.y <= pos.y * 16 + 188) {
	pge->FillRectDecal(
		{pos.x * 16 + 6.0f, pos.y * 16 + 122},
		{210, 54},
		olc::GREY
		);
	pge->DrawStringDecal(
		{pos.x * 16 + 8.0f, pos.y * 16 + 124},
		title,
		olc::BLACK);
	pge->DrawStringDecal(
		{pos.x * 16 + 8.0f, pos.y * 16 + 140},
		flavour,
		olc::DARK_BLUE);
	if (!completed) {
	    pge->DrawStringDecal(
		    {pos.x * 16 + 160.0f, pos.y * 16 + 124},
		    std::to_string(cost) + "ip",
		    internetPoints < cost ? olc::RED : olc::GREEN);
	}
    }
}

const std::vector<std::string> &SkillTree::SkillTreeNode::getDependecies() const {
    return deps;
}

olc::vf2d SkillTree::SkillTreeNode::getPos() const {
    return pos;
}

bool SkillTree::SkillTreeNode::isCompleted() const {
    return completed;
}

bool SkillTree::SkillTreeNode::isCompletable(const SkillTree &skillTree) const {
    return std::all_of(deps.begin(), deps.end(), [&](const auto &dep){
	    return skillTree.isSkillComplete(dep);
	    });
}

void SkillTree::SkillTreeNode::complete() {
    completed = true;
    for (int i = 0; i < 8; i++) {
	graphic.Sprite()->SetPixel(i, 0, olc::Pixel(16, 165, 0));
	graphic.Sprite()->SetPixel(i, 7, olc::Pixel(16, 165, 0));
	graphic.Sprite()->SetPixel(0, i, olc::Pixel(16, 165, 0));
	graphic.Sprite()->SetPixel(7, i, olc::Pixel(16, 165, 0));
    }
    graphic.Decal()->Update();
}

bool SkillTree::SkillTreeNode::tick(olc::PixelGameEngine *pge,
	const SkillTree &skillTree,
	std::int64_t &internetPoints) {
    const auto mousePos = pge->GetMousePos();
    if (mousePos.x >= pos.x * 16 + 80 && mousePos.x <= pos.x * 16 + 88 &&
		mousePos.y >= pos.y * 16 + 180 && mousePos.y <= pos.y * 16 + 188 &&
		pge->GetMouse(0).bPressed &&
		!completed &&
		isCompletable(skillTree) &&
		cost <= internetPoints) {
	    complete();
	    internetPoints -= cost;
	    return true;
    }
    return false;
}
