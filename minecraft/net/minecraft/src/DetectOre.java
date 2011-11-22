package net.minecraft.src;

import java.awt.image.BufferedImage;
import java.io.InputStream;

import javax.imageio.ImageIO;

import net.minecraft.client.Minecraft;

public class DetectOre extends Item
{	
	public DetectOre(int i, int detectedID, int itemIconIndex)
	{
		super(i);
		
		ModLoader.RegisterEntityID(this.getClass(), "Ore detector", i);
		iconIndex = ModLoader.getUniqueSpriteIndex("/gui/items.png");

		this.detectedID = detectedID;
		iconAnimation = new TextureDetectOreFX(iconIndex, detectedID, itemIconIndex);
    	lastTickTime = 0;
    	setRange(17);
        setStackType(DetectOreStack.class);
	}

	public boolean OnTickInGame(float tick, Minecraft mc)
	{
    	boolean bOreFounded = false;
    	double distanceMin = -1;
    	
		if(mc.theWorld != null && mc.thePlayer != null)
        {
        	int playerX, playerY, playerZ;
        	playerX = (int) mc.thePlayer.posX;
        	playerY = (int) mc.thePlayer.posY - 1;
        	playerZ = (int) mc.thePlayer.posZ;
        	
        	
        	for(int i = -range; i < range; ++i)
        		for(int j = -range; j < range; ++j)
        			for(int k = -range; k < range; ++k)
        			{
        				int iScannedID = mc.theWorld.getBlockId(playerX + i, playerY + j, playerZ + k);
        				if(iScannedID == detectedID)
        				{
        					bOreFounded = true;

	        				double distance = Math.sqrt(i * i + j * j + k * k);
	        				if(distanceMin == -1 || distance < distanceMin)
	        					distanceMin = distance;
        				}
        			}
        }

        if(bOreFounded)
        {
        	if(System.currentTimeMillis() - lastTickTime > distanceMin * 25)
        	{
        		lastTickTime = System.currentTimeMillis();
        		mc.sndManager.playSoundFX("random.click", 1.0F, 1.0F);
        	}
        }
        
        return true;
	}
	
	public TextureFX getIconAnimation()
	{
		return iconAnimation;
	}
	
	public void setRange(int iNewRange)
	{
		range = iNewRange;
	}
	
	private int range;
	private long lastTickTime;
	private int detectedID;
	private TextureDetectOreFX iconAnimation;
}
