#ifndef WIDGETWITHBACKGROUND_H
#define WIDGETWITHBACKGROUND_H

#include <QWidget>

class QPixmap;

class WidgetWithBackground : public QWidget
{
	Q_OBJECT
  public:
     /** Konstruktor */
     WidgetWithBackground(QWidget * parent = 0);

     /** Destruktor - usuwa bitmapk?  */
     ~WidgetWithBackground ();

     /**
      * Operacja odmalowywania kontrolki  -
      * wkleja bitmap?z t³em na kontrolk?-
      * generuj±æ j?wcze¶niej je¿eli zajdzie taka potrzeba.
      */
     void  drawBackground ();

     /** Odmalowywuje kontrolk?bezwarunkowo odmalowywuj±c t³o. */
     void  updateWithBackground ();
    
     /** 
     * Zawraca informacje czy kontrolka zosta³a zmodyfikowana
     * Ta informacja jest ustawiana gdy bitmapka t³a si?zmienia 
     * to znaczy zmienia si?rozmiar komponentu lub istnieje 
     * potrzeba przemalowania t³a. 
     */ 
     bool doRepaintBackground(); 
     
  protected:
    /** Wywo³uje paintBackground - odmalowywuj±c t³o na nowo */
    void repaintBackground();

    /**
     * Odmalowywuje t³o kontrolki
     * @param painter urz±dzenie na ktróym mamy malowa?
     * @param background to t³o kontrolki
     */
    virtual void  paintBackground (QPainter & painer) = 0;
    
    

  protected:
     /** Bufor na t³o. */
     QPixmap * m_pixmap;
     /**
     * Ustawia t?zmienn?po zmianie w³a¶ciwo¶ci
     */
     bool m_modified;
};
#endif //WIDGETWITHBACKGROUND_H

