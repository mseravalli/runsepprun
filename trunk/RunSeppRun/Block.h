/* 
 * File:   Block.h
 * Author: marco
 *
 * Created on April 12, 2010, 3:17 PM
 */

#ifndef _BLOCK_H
#define	_BLOCK_H

#include "WorldElement.h"


class Block : public WorldElement {
public:
    Block();
    Block(const Block& orig);
    virtual ~Block();
private:

};

#endif	/* _BLOCK_H */

