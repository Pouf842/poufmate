package net.minecraft.src;

import org.lwjgl.opengl.GL11;

public class DetectOreStack extends ItemStack
{
	public DetectOreStack(DetectOreStack copy)
	{
		super(copy);
		range = copy.getRange();
	}

	public DetectOreStack(ItemStack stack)
	{
		super(stack);
		
		range = 0;
	}

	public DetectOreStack(DetectOre item) {
		super(item, 1);
		
		range = 0;
	}

	public DetectOreStack(Item item) {
		super(item, 1);
		
		range = 0;
	}

	public DetectOreStack setRange(int iNewRange)
	{
		range = iNewRange;
		return this;
	}

	public int getRange()
	{
		return range;
	}

	@Override
	public ItemStack setCreativeContainerMode(boolean b)
	{
		setRange(64);
		return this;
	}
	
	@Override
	public DetectOreStack copy()
	{
		return new DetectOreStack(this);
	}
	
	@Override
	public void renderStack(RenderItem itemRender, FontRenderer fontrenderer, RenderEngine renderengine, int i, int j)
	{
		if(range != 0)
		{
	        String s = (new StringBuilder()).append("").append(range).toString();
	        GL11.glDisable(2896 /*GL_LIGHTING*/);
	        GL11.glDisable(2929 /*GL_DEPTH_TEST*/);
	        fontrenderer.drawStringWithShadow(s, i, j + 6 + 3, 0x7777ff);
	        GL11.glEnable(2896 /*GL_LIGHTING*/);
	        GL11.glEnable(2929 /*GL_DEPTH_TEST*/);
		}
	}
	
	@Override
    public NBTTagCompound writeToNBT(NBTTagCompound nbttagcompound)
    {
		super.writeToNBT(nbttagcompound);
        nbttagcompound.setByte("Range", (byte) range);
        nbttagcompound.setString("Type", this.getClass().getCanonicalName());
        return nbttagcompound;
    }

	@Override
    public void readFromNBT(NBTTagCompound nbttagcompound)
    {
    	super.readFromNBT(nbttagcompound);
        range = nbttagcompound.getByte("Range");
    }

	public static ItemStack loadItemStackFromNBT(NBTTagCompound nbttagcompound)
	{	
		DetectOreStack stackToReturn = new DetectOreStack(ItemStack.loadItemStackFromNBT(nbttagcompound));
        stackToReturn.setRange(nbttagcompound.getByte("Range"));
        
        return stackToReturn;
	}

	private int range;
}
