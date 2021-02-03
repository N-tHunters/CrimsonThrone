/**
 * \file
 * \brief This file contains implementation of Missle
 */
#include "missle.hpp"
#include "entries.hpp"

/**
 * Convert object to binary stream.
 * \param saver Serializer
 * \return Binary stream representing this object
 */
std::stringstream * Missle::Save(Saver* saver) {
  return StackableItem::Save(saver, ENTRY_MISSLE);
}
