// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) braces deadcode 

package net.minecraft.src;

import org.lwjgl.opengl.GL11;


// Referenced classes of package net.minecraft.src:
//            Block, Item, StatList, EntityPlayer, 
//            NBTTagCompound, World, Entity, EntityLiving, 
//            EnumAction

public class ItemStack
{
	public ItemStack(ItemStack itemstack)
	{
		this(itemstack.itemID, itemstack.stackSize, itemstack.itemDamage);
	}
	
    public ItemStack(Block block)
    {
        this(block, 1);
    }

    public ItemStack(Block block, int i)
    {
        this(block.blockID, i, 0);
    }

    public ItemStack(Block block, int i, int j)
    {
        this(block.blockID, i, j);
    }

    public ItemStack(Item item)
    {
        this(item.shiftedIndex, 1, 0);
    }

    public ItemStack(Item item, int i)
    {
        this(item.shiftedIndex, i, 0);
    }

    public ItemStack(Item item, int i, int j)
    {
        this(item.shiftedIndex, i, j);
    }

    public ItemStack(int i, int j, int k)
    {
        stackSize = 0;
        itemID = i;
        stackSize = j;
        itemDamage = k;
    }

	public ItemStack setCreativeContainerMode(boolean b)
	{
		return this;
	}
	
    public static ItemStack loadItemStackFromNBT(NBTTagCompound nbttagcompound)
    {
        ItemStack itemstack = new ItemStack();
        itemstack.readFromNBT(nbttagcompound);
        return itemstack.getItem() == null ? null : itemstack;
    }

    private ItemStack()
    {
        stackSize = 0;
    }

    public ItemStack splitStack(int i)
    {
        stackSize -= i;
        return this.copy().setSize(i);
    }

    public Item getItem()
    {
        return Item.itemsList[itemID];
    }

    public int getIconIndex()
    {
        return getItem().getIconIndex(this);
    }

    public boolean useItem(EntityPlayer entityplayer, World world, int i, int j, int k, int l)
    {
        boolean flag = getItem().onItemUse(this, entityplayer, world, i, j, k, l);
        if(flag)
        {
            entityplayer.addStat(StatList.objectUseStats[itemID], 1);
        }
        return flag;
    }

    public float getStrVsBlock(Block block)
    {
        return getItem().getStrVsBlock(this, block);
    }

    public ItemStack useItemRightClick(World world, EntityPlayer entityplayer)
    {
        return getItem().onItemRightClick(this, world, entityplayer);
    }

    public ItemStack onFoodEaten(World world, EntityPlayer entityplayer)
    {
        return getItem().onFoodEaten(this, world, entityplayer);
    }

    public NBTTagCompound writeToNBT(NBTTagCompound nbttagcompound)
    {
    	nbttagcompound.setString("Type", this.getClass().getCanonicalName());
        nbttagcompound.setShort("id", (short)itemID);
        nbttagcompound.setByte("Count", (byte)stackSize);
        nbttagcompound.setShort("Damage", (short)itemDamage);
        return nbttagcompound;
    }

    public void readFromNBT(NBTTagCompound nbttagcompound)
    {
        itemID = nbttagcompound.getShort("id");
        stackSize = nbttagcompound.getByte("Count");
        itemDamage = nbttagcompound.getShort("Damage");
    }

    public int getMaxStackSize()
    {
        return getItem().getItemStackLimit();
    }

    public boolean isStackable()
    {
        return getMaxStackSize() > 1 && (!isItemStackDamageable() || !isItemDamaged());
    }

    public boolean isItemStackDamageable()
    {
        return Item.itemsList[itemID].getMaxDamage() > 0;
    }

    public boolean getHasSubtypes()
    {
        return Item.itemsList[itemID].getHasSubtypes();
    }

    public boolean isItemDamaged()
    {
        return isItemStackDamageable() && itemDamage > 0;
    }

    public int getItemDamageForDisplay()
    {
        return itemDamage;
    }

    public int getItemDamage()
    {
        return itemDamage;
    }

    public void setItemDamage(int i)
    {
        itemDamage = i;
    }

    public int getMaxDamage()
    {
        return Item.itemsList[itemID].getMaxDamage();
    }

    public void damageItem(int i, Entity entity)
    {
        if(!isItemStackDamageable())
        {
            return;
        }
        itemDamage += i;
        if(itemDamage > getMaxDamage())
        {
            if(entity instanceof EntityPlayer)
            {
                ((EntityPlayer)entity).addStat(StatList.objectBreakStats[itemID], 1);
            }
            stackSize--;
            if(stackSize < 0)
            {
                stackSize = 0;
            }
            itemDamage = 0;
        }
    }

    public void hitEntity(EntityLiving entityliving, EntityPlayer entityplayer)
    {
        boolean flag = Item.itemsList[itemID].hitEntity(this, entityliving, entityplayer);
        if(flag)
        {
            entityplayer.addStat(StatList.objectUseStats[itemID], 1);
        }
    }

    public void onDestroyBlock(int i, int j, int k, int l, EntityPlayer entityplayer)
    {
        boolean flag = Item.itemsList[itemID].onBlockDestroyed(this, i, j, k, l, entityplayer);
        if(flag)
        {
            entityplayer.addStat(StatList.objectUseStats[itemID], 1);
        }
    }

    public int getDamageVsEntity(Entity entity)
    {
        return Item.itemsList[itemID].getDamageVsEntity(entity);
    }

    public boolean canHarvestBlock(Block block)
    {
        return Item.itemsList[itemID].canHarvestBlock(block);
    }

    public void onItemDestroyedByUse(EntityPlayer entityplayer)
    {
    }

    public void useItemOnEntity(EntityLiving entityliving)
    {
        Item.itemsList[itemID].saddleEntity(this, entityliving);
    }

    public ItemStack copy()
    {
        return new ItemStack(itemID, stackSize, itemDamage);
    }

    public static boolean areItemStacksEqual(ItemStack itemstack, ItemStack itemstack1)
    {
        if(itemstack == null && itemstack1 == null)
        {
            return true;
        }
        if(itemstack == null || itemstack1 == null)
        {
            return false;
        } else
        {
            return itemstack.isItemStackEqual(itemstack1);
        }
    }

    private boolean isItemStackEqual(ItemStack itemstack)
    {
        if(stackSize != itemstack.stackSize)
        {
            return false;
        }
        if(itemID != itemstack.itemID)
        {
            return false;
        }
        return itemDamage == itemstack.itemDamage;
    }

    public boolean isItemEqual(ItemStack itemstack)
    {
        return itemID == itemstack.itemID && itemDamage == itemstack.itemDamage;
    }

    public String getItemName()
    {
        return Item.itemsList[itemID].getItemNameIS(this);
    }

    public static ItemStack copyItemStack(ItemStack itemstack)
    {
        return itemstack != null ? itemstack.copy() : null;
    }

    public String toString()
    {
        return (new StringBuilder()).append(stackSize).append("x").append(Item.itemsList[itemID].getItemName()).append("@").append(itemDamage).toString();
    }

    public void updateAnimation(World world, Entity entity, int i, boolean flag)
    {
        if(animationsToGo > 0)
        {
            animationsToGo--;
        }
        Item.itemsList[itemID].onUpdate(this, world, entity, i, flag);
    }

    public void onCrafting(World world, EntityPlayer entityplayer)
    {
        entityplayer.addStat(StatList.objectCraftStats[itemID], stackSize);
        Item.itemsList[itemID].onCreated(this, world, entityplayer);
    }

    public boolean isStackEqual(ItemStack itemstack)
    {
        return itemID == itemstack.itemID && stackSize == itemstack.stackSize && itemDamage == itemstack.itemDamage;
    }

    public int getMaxItemUseDuration()
    {
        return getItem().getMaxItemUseDuration(this);
    }

    public EnumAction getItemUseAction()
    {
        return getItem().getItemUseAction(this);
    }

    public void onPlayerStoppedUsing(World world, EntityPlayer entityplayer, int i)
    {
        getItem().onPlayerStoppedUsing(this, world, entityplayer, i);
    }

    public ItemStack setSize(int iNewSize)
    {
    	stackSize = iNewSize;
    	return this;
    }
    
    public void renderStack(RenderItem itemRender, FontRenderer fontrenderer, RenderEngine renderengine, int i, int j)
    {
        if(stackSize > 1)
        {
            String s = (new StringBuilder()).append("").append(stackSize).toString();
            GL11.glDisable(2896 /*GL_LIGHTING*/);
            GL11.glDisable(2929 /*GL_DEPTH_TEST*/);
            fontrenderer.drawStringWithShadow(s, (i + 19) - 2 - fontrenderer.getStringWidth(s), j + 6 + 3, 0xffffff);
            GL11.glEnable(2896 /*GL_LIGHTING*/);
            GL11.glEnable(2929 /*GL_DEPTH_TEST*/);
        }

        if(isItemDamaged())
        {
            int k = (int)Math.round(13D - ((double) getItemDamageForDisplay() * 13D) / (double) getMaxDamage());
            int l = (int)Math.round(255D - ((double) getItemDamageForDisplay() * 255D) / (double) getMaxDamage());
            GL11.glDisable(2896 /*GL_LIGHTING*/);
            GL11.glDisable(2929 /*GL_DEPTH_TEST*/);
            GL11.glDisable(3553 /*GL_TEXTURE_2D*/);
            Tessellator tessellator = Tessellator.instance;
            int i1 = 255 - l << 16 | l << 8;
            int j1 = (255 - l) / 4 << 16 | 0x3f00;
            itemRender.renderQuad(tessellator, i + 2, j + 13, 13, 2, 0);
            itemRender.renderQuad(tessellator, i + 2, j + 13, 12, 1, j1);
            itemRender.renderQuad(tessellator, i + 2, j + 13, k, 1, i1);
            GL11.glEnable(3553 /*GL_TEXTURE_2D*/);
            GL11.glEnable(2896 /*GL_LIGHTING*/);
            GL11.glEnable(2929 /*GL_DEPTH_TEST*/);
            GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
        }
    }
    
    public int stackSize;
    public int animationsToGo;
    public int itemID;
    private int itemDamage;
}
