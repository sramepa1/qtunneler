/* 
 * File:   InitDialog.h
 * Author: pavel
 *
 * Created on 19. březen 2010, 12:26
 */

#ifndef _INITDIALOG_H
#define	_INITDIALOG_H

#include "ui_InitDialog.h"

class InitDialog : public QDialog {
    Q_OBJECT
public:
    InitDialog();
    virtual ~InitDialog();
private:
    Ui::InitDialog widget;
};

#endif	/* _INITDIALOG_H */
