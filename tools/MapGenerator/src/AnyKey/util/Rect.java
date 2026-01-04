/*
 * Map Generator for 'Gods Defense'
 * @author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
 */
package AnyKey.util;

import java.awt.Color;
import java.awt.Graphics;

public class Rect {
    static int rectX;
    static int rectY;
    static int rectW;
    static int rectH;
    static Graphics graph;
    static Rect rect;

    public static Rect getInstace() {
        if (rect == null) {
            rect = new Rect();
        }
        return rect;
    }

    public static Rect buildRect(Graphics g, int x, int y, int width, int height) {
        Rect.setRectInfo(x, y, width, height);
        g.setColor(Color.RED);
        g.drawRect(x, y, width, height);
        graph = g;
        return rect;
    }

    private static void setRectInfo(int x, int y, int width, int height) {
        rectX = x;
        rectY = y;
        rectW = width;
        rectH = height;
    }

    public boolean contains(int pX, int pY) {
        return pX >= rectX && pX <= rectX + rectW && pY >= rectY && pY <= rectY + rectH;
    }
}
