#pragma once

/*!
\file blockContactListener.h
*/

#include <Box2D\Box2D.h>

#include "dynamicBlock.h"
#include "staticBlock.h"

/*! \class blockContactListener
\brief A listener which listens for contacts between balls and blocks and changes block colours
*/

class BlockCircleContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact); //!< Called when two fixtures begin to touch
	void EndContact(b2Contact* contact); //!< Called when two fixtures cease to touch
};