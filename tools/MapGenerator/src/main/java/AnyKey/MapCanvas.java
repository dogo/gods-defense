/*
 * Map Generator for 'Gods Defense'
 * @author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
 */
package AnyKey;

import AnyKey.Checkpoints;
import AnyKey.MapWindow;
import AnyKey.util.Rect;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.awt.image.RenderedImage;
import java.io.File;
import java.io.IOException;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.imageio.ImageIO;
import javax.swing.JPanel;
import javax.swing.event.MouseInputListener;

public class MapCanvas
extends JPanel
implements MouseInputListener {
    private Point lastPoint;
    private Color color;
    private final int MAP_HEIGHT = 480;
    private final int MAP_WIDTH = 480;
    private final int TILE_SIZE = 32;
    private final int LEFT_SIDE = 16;
    private final int RIGHT_SIDE = 464;
    private final int UPPER_SIDE = 16;
    private final int DOWN_SIDE = 464;
    public static String[][] mCollisionMap;
    public Color[][] buffer;
    public Boolean clear = false;
    public Boolean mCheckButtonIsOn = false;
    public static Vector<Checkpoints> mCheckpointsVector;
    public int click;
    private BufferedImage mMapImg = null;
    private BufferedImage bi = null;
    private Graphics2D ig2;

    MapCanvas() {
        this.setSize(600, 500);
        this.setVisible(true);
        this.addMouseListener(this);
        this.addMouseMotionListener(this);
        mCollisionMap = new String[15][15];
        this.buffer = new Color[15][15];
        this.click = 0;
        this.bi = new BufferedImage(480, 480, 1);
        this.ig2 = this.bi.createGraphics();
    }

    public void paintComponent(Graphics g) {
        this.drawMapAlpha(g);
        this.drawBuffer(g);
        this.drawArea(this.lastPoint, g);
        Rect.buildRect(g, 0, 0, 480, 480);
        this.drawGrid(g);
        this.drawChooseColor(g);
        if (this.clear.booleanValue()) {
            this.clearGrid(g);
            Rect.buildRect(g, 0, 0, 480, 480);
            this.drawGrid(g);
            this.clear = false;
        }
    }

    public boolean save2Png() {
        try {
            if (!this.bufferIsEmpty()) {
                ImageIO.write((RenderedImage)this.bi, "PNG", new File(MapWindow.mMapWindowReference.getName() + ".PNG"));
                this.ig2.dispose();
                return true;
            }
        }
        catch (IOException ex) {
            Logger.getLogger(MapCanvas.class.getName()).log(Level.SEVERE, null, ex);
        }
        return false;
    }

    public void drawBuffer(Graphics g) {
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                if (this.buffer[i][j] == null) continue;
                if (this.buffer[i][j].equals(Color.GREEN)) {
                    g.setColor(Color.GREEN);
                    this.ig2.setColor(Color.GREEN);
                } else {
                    g.setColor(Color.RED);
                    this.ig2.setColor(Color.RED);
                }
                g.fillRect(i * 32, j * 32, 32, 32);
                this.ig2.fillRect(i * 32, j * 32, 32, 32);
            }
        }
    }

    public void drawGrid(Graphics g) {
        g.setColor(Color.BLACK);
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                g.drawRect(i * 32, j * 32, 32, 32);
            }
        }
    }

    public void drawChooseColor(Graphics g) {
        g.setColor(Color.RED);
        g.fillRect(500, 10, 32, 32);
        g.setColor(Color.GREEN);
        g.fillRect(500, 50, 32, 32);
    }

    public void genMapCollison(int x, int y, Color color) {
        if (color.equals(Color.RED)) {
            MapCanvas.mCollisionMap[x][y] = "#";
        } else if (color.equals(Color.GREEN)) {
            MapCanvas.mCollisionMap[x][y] = "_";
        }
    }

    public void clearGrid(Graphics g) {
        this.clearBuffer();
        g.setColor(this.getBackground());
        g.fillRect(0, 0, 480, 480);
        this.click = 0;
        this.mMapImg = null;
    }

    private void clearBuffer() {
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                this.buffer[i][j] = null;
            }
        }
    }

    private boolean bufferIsEmpty() {
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j < 15; ++j) {
                if (this.buffer[i][j] != null) continue;
                return true;
            }
        }
        return false;
    }

    public void setMapAlpha(String aPath) {
        if (this.mMapImg == null) {
            try {
                this.mMapImg = ImageIO.read(new File(aPath));
            }
            catch (IOException ex) {
                Logger.getLogger(MapCanvas.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }

    private void drawMapAlpha(Graphics g) {
        if (this.mMapImg != null) {
            g.drawImage(this.mMapImg, 0, 0, this);
        }
    }

    public void drawArea(Point point, Graphics g) {
        if (point != null && this.color != null) {
            g.setColor(this.color);
            for (int i = 0; i < 15; ++i) {
                for (int j = 0; j < 15; ++j) {
                    if (i * 32 >= point.x || point.x >= i * 32 + 32 || j * 32 >= point.y || point.y >= j * 32 + 32) continue;
                    this.genMapCollison(i, j, this.color);
                    g.fillRect(i * 32, j * 32, 32, 32);
                    this.buffer[i][j] = this.color;
                }
            }
        }
    }

    public static boolean touchedInRect(Rect aRect, Point touchCurLocation) {
        return aRect.contains(touchCurLocation.x, touchCurLocation.y);
    }

    public void processEvents(MouseEvent e) {
        if (e.getX() >= 500 && e.getX() <= 532 && e.getY() >= 10 && e.getY() <= 42) {
            this.color = Color.RED;
        } else if (e.getX() >= 500 && e.getX() <= 532 && e.getY() >= 50 && e.getY() <= 82) {
            this.color = Color.GREEN;
        } else if (MapCanvas.touchedInRect(Rect.getInstace(), e.getPoint())) {
            this.lastPoint = e.getPoint();
            this.repaint();
        }
    }

    public void mousePressed(MouseEvent e) {
        if (this.mCheckButtonIsOn.booleanValue()) {
            int x = e.getX() / 32 * 32 + 16;
            int y = e.getY() / 32 * 32 + 16;
            if (MapWindow.mMapWindowReference.getjCheckBoxStartPoint().isSelected() || MapWindow.mMapWindowReference.getjCheckBoxEndPoint().isSelected()) {
                MapWindow.mMapWindowReference.getjCheckBoxStartPoint().setSelected(false);
                MapWindow.mMapWindowReference.getjCheckBoxEndPoint().setSelected(false);
                if (x == 16) {
                    x -= 32;
                } else if (x == 464) {
                    x += 32;
                } else if (x == 16) {
                    y -= 32;
                } else if (x == 464) {
                    y += 32;
                }
            }
            mCheckpointsVector.add(new Checkpoints(Integer.toString(x), Integer.toString(y), "1"));
            ++this.click;
            MapWindow.mMapWindowReference.addCheckpointToCombo(Integer.toString(x), Integer.toString(y));
        } else {
            this.processEvents(e);
        }
    }

    public void mouseDragged(MouseEvent e) {
        if (e.getX() >= 0 && e.getX() <= 480 && e.getY() >= 0 && e.getY() <= 480) {
            this.processEvents(e);
        }
    }

    public void mouseClicked(MouseEvent e) {
    }

    public void mouseMoved(MouseEvent e) {
    }

    public void mouseReleased(MouseEvent e) {
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }

    static {
        mCheckpointsVector = new Vector<Checkpoints>();
    }
}
