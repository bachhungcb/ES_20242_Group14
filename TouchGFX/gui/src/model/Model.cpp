#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "../../../Shared/PatternManager.hpp"
Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

void Model::init()
{
    PatternManager::getInstance().loadPattern();
}
