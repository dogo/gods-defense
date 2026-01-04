/*
 * Map Generator for 'Gods Defense'
 * @author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
 */
package AnyKey;

public class Waves {
    private Boolean mIsBoss;
    private String mNumberOfEnemies;
    private String mEnemyFolder;
    private String mWaveDescription;
    private String mIntervalSpawnTime;

    public Waves(Boolean aIsBoss, String aNumberOfEnemies, String aEnemyFolder, String aWaveDescription, String aIntervalSpawnTime) {
        this.mIsBoss = aIsBoss;
        this.mNumberOfEnemies = aNumberOfEnemies;
        this.mEnemyFolder = aEnemyFolder;
        this.mWaveDescription = aWaveDescription;
        this.mIntervalSpawnTime = aIntervalSpawnTime;
    }

    public String getEnemyFolder() {
        return this.mEnemyFolder;
    }

    public void setEnemyFolder(String aEnemyFolder) {
        this.mEnemyFolder = aEnemyFolder;
    }

    public String getIntervalSpawnTime() {
        return this.mIntervalSpawnTime;
    }

    public void setIntervalSpawnTime(String aIntervalSpawnTime) {
        this.mIntervalSpawnTime = aIntervalSpawnTime;
    }

    public Boolean getIsBoss() {
        return this.mIsBoss;
    }

    public void setIsBoss(Boolean aIsBoss) {
        this.mIsBoss = aIsBoss;
    }

    public String getNumberOfEnemies() {
        return this.mNumberOfEnemies;
    }

    public void setNumberOfEnemies(String aNumberOfEnemies) {
        this.mNumberOfEnemies = aNumberOfEnemies;
    }

    public String getWaveDescription() {
        return this.mWaveDescription;
    }

    public void setWaveDescription(String aWaveDescription) {
        this.mWaveDescription = aWaveDescription;
    }
}
