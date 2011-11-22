package net.minecraft.src;

import java.util.Map.Entry;
import java.util.HashMap;

import net.minecraft.client.Minecraft;

public class mod_detectOres extends BaseMod
{
	public mod_detectOres()
	{	
		baseItemList.put(Item.diamond, Block.oreDiamond.blockID);
		baseItemList.put(Item.ingotIron, Block.oreIron.blockID);
		baseItemList.put(Item.coal,Block.oreCoal.blockID);
		baseItemList.put(Item.ingotGold, Block.oreGold.blockID);
		baseItemList.put(Item.redstone, Block.oreRedstone.blockID);
		
		for(Object entry : baseItemList.entrySet())
		{
			Item item = (Item) ((Entry) entry).getKey();
			int blockID = (Integer) ((Entry) entry).getValue();
			
			DetectOre detectOre = new DetectOre(ModLoader.getUniqueEntityId(), blockID, item.getIconFromDamage(0));
			String sDetectOreName = item.getStatName() + " detector";
			detectOre.setItemName(sDetectOreName).setMaxStackSize(1);

			detectOres.put(item, detectOre);
			ModLoader.AddName(detectOre, sDetectOreName);
			ModLoader.AddRecipe(new DetectOreStack(detectOre), new Object[] {recipesPattern, Character.valueOf('#'), Item.stick, Character.valueOf('X'), Item.redstone, Character.valueOf('Y'), item});
			ModLoader.SetInGameHook(this, true, true);
			ModLoader.SetInGUIHook(this, true, true);
		}
		
		lastUsedDetectOre = null;
	}

	@Override
	public String Version()
	{
		return "1.8.1";
	}
	
	@Override
	public boolean OnTickInGUI(float f, Minecraft mc, GuiScreen guiscreen)
	{
		if(guiscreen instanceof GuiCrafting)
		{
			ContainerWorkbench workBench = (ContainerWorkbench) ((GuiCrafting) guiscreen).inventorySlots;
			
			if(workBench.craftResult.getStackInSlot(0) instanceof DetectOreStack)
			{
				int iRange = workBench.craftMatrix.getStackInSlot(6).stackSize / 4 + 4;
				
				((DetectOreStack) workBench.craftResult.getStackInSlot(0)).setRange(iRange);
			}
		}
		
		return true;
	}
	
	@Override
	public boolean OnTickInGame(float tick, Minecraft game)
	{
		ItemStack currentItemStack = game.thePlayer.inventory.getCurrentItem();
		
		if(currentItemStack != null)
		{						
			if(currentItemStack instanceof DetectOreStack)
			{
				DetectOre detectOre = (DetectOre) currentItemStack.getItem();
				
				if(currentItemStack != lastUsedDetectOre)
				{
					lastUsedDetectOre = currentItemStack;
					detectOre.setRange(((DetectOreStack) currentItemStack).getRange());
				}
				
				detectOre.OnTickInGame(tick, game);
			}
		}

		return true;
	}
	
	public void RegisterAnimation(Minecraft mc)
	{
		for(Object obj : detectOres.values())
		{
			DetectOre detectOre = (DetectOre) obj;
			ModLoader.addAnimation(detectOre.getIconAnimation());
		}
	}

	@Override
	public void TakenFromCrafting(EntityPlayer entityplayer, ItemStack itemstack, IInventory iinventory)
	{	
		if(itemstack instanceof DetectOreStack)
		{
			iinventory.getStackInSlot(6).stackSize -= (((DetectOreStack) itemstack).getRange() - 1) * 4;
		}
	}

	public static final HashMap detectOres = new HashMap();// = new DetectOre(ModLoader.getUniqueEntityId(), 0);
	public static final HashMap baseItemList = new HashMap();
	public static final String recipesPattern[] = {" # ", " # ", "XY "};
	public static ItemStack lastUsedDetectOre;
}
