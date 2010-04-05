/* 
 * File:   View.h
 * Author: pavel
 *
 * Created on 5. duben 2010, 10:51
 */

#ifndef _VIEW_H
#define	_VIEW_H

#include <QObject>
#include <QWidget>

class View : public QWidget {

    Q_OBJECT

public:
    View(QWidget* parent = NULL);
    virtual ~View();

protected:

};

#endif	/* _VIEW_H */

