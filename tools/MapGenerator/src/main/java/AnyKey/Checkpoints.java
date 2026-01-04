/*
 * Map Generator for 'Gods Defense'
 * @author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
 */
package AnyKey;

public class Checkpoints {
    private String mRadius;
    private String mCoordX;
    private String mCoordY;

    public Checkpoints(String aCoordX, String aCoordY, String aRadius) {
        this.mCoordX = aCoordX;
        this.mCoordY = aCoordY;
        this.mRadius = aRadius;
    }

    public String getRadius() {
        return this.mRadius;
    }

    public void setRadius(String aRadius) {
        this.mRadius = aRadius;
    }

    public String getCoordX() {
        return this.mCoordX;
    }

    public void setCoordX(String aCoordX) {
        this.mCoordX = aCoordX;
    }

    public String getCoordY() {
        return this.mCoordY;
    }

    public void setCoordY(String aCoordY) {
        this.mCoordY = aCoordY;
    }
}
