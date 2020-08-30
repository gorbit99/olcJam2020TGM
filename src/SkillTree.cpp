#include "SkillTree.h"

void SkillTree::addNode(std::string title,
	std::string flavourText,
	std::string graphicPath,
	int tier) {
    nodes[title] = std::move(SkillTreeNode{
	    title,
	    flavourText,
	    graphicPath,
	    {float(tier), float(tierCounts[tier]) + tier * 0.25f}
	    });
    tierCounts[tier]++;
}

void SkillTree::addDependency(std::string dependant, std::string dependency) {
    nodes[dependant].addDependency(dependency);
}

bool SkillTree::isSkillComplete(std::string skill) const {
    return nodes.at(skill).isCompleted();
}

void SkillTree::drawSelf(olc::PixelGameEngine *pge) const {
    for (auto &node : nodes) {
	node.second.drawSelf(pge);
	for (const auto &dependency : node.second.getDependecies()) {
	    const auto &depNode = nodes.at(dependency);
	    const auto posFrom = depNode.getPos() * 40 + olc::vi2d{8, 8};
	    const auto posTo = node.second.getPos() * 40 + olc::vi2d{8, 8};
	    const auto color = depNode.isCompleted() ? olc::GREEN : olc::RED;
	    pge->DrawLine(posFrom, posTo, color);
	}
    }
}

void SkillTree::tick(olc::PixelGameEngine *pge) {
    for (auto &node : nodes) {
	node.second.tick(pge, *this);
    }
}

SkillTree::SkillTreeNode::SkillTreeNode(std::string title,
	std::string flavourText,
	std::string graphicPath,
	olc::vf2d pos)
    : title{title}, flavour{flavourText}, pos{pos}
{
    graphic = std::make_unique<olc::Renderable>();
    graphic->Load(graphicPath);
}

void SkillTree::SkillTreeNode::addDependency(std::string dependency) {
    deps.push_back(dependency);
}

void SkillTree::SkillTreeNode::drawSelf(olc::PixelGameEngine *pge) const {
    pge->DrawDecal(pos * 40, graphic->Decal());
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
}

void SkillTree::SkillTreeNode::tick(olc::PixelGameEngine *pge,
	const SkillTree &skillTree) {
    const auto mousePos = pge->GetMousePos();
    if (mousePos.x >= pos.x * 40 && mousePos.x <= pos.x * 40 + 16 &&
	    mousePos.y >= pos.y * 40 && mousePos.y <= pos.y * 40 + 16 &&
	    pge->GetMouse(0).bPressed &&
	    isCompletable(skillTree)) {
	completed = true;
    }
}
