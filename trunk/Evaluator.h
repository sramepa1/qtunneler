/* 
 * File:   Evaluator.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 11:42
 */

#ifndef _EVALUATOR_H
#define	_EVALUATOR_H

class Evaluator {
public:
    Evaluator();    
    virtual ~Evaluator();
    
private:
    Evaluator(const Evaluator& orig) {} // disabled
};

#endif	/* _EVALUATOR_H */

