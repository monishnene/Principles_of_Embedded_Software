dma_st memmove_dma(uint8_t *src, uint8_t *dst, uint32_t length)
{       
        uint32_t i;
        uint8_t j;
        uint16_t k;
	SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
	DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK;
	DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;

        if(dst<src || dst>(src+length))
     {
	DMA_SAR0 =  src;
	DMA_DAR0 =  dst;
     }
       if(length== i)
      {
        DMA_DSR_BCR0 |= length;         
	DMA_DCR0 |= DMA_DCR_SINC_MASK;	
	DMA_DCR0 |= DMA_DCR_SSIZE(0);	
	DMA_DCR0 |= DMA_DCR_DINC_MASK;	
	DMA_DCR0 |= DMA_DCR_DSIZE(0);
       }
        else if(length == j)
       { 
         DMA_DSR_BCR0 |= length;         
	DMA_DCR0 |= DMA_DCR_SINC_MASK;	
	DMA_DCR0 |= DMA_DCR_SSIZE(1);	
	DMA_DCR0 |= DMA_DCR_DINC_MASK;	
	DMA_DCR0 |= DMA_DCR_DSIZE(1);
	}
        else (length == k)
        {
        DMA_DSR_BCR0 |= length;         
	DMA_DCR0 |= DMA_DCR_SINC_MASK;	
	DMA_DCR0 |= DMA_DCR_SSIZE(10);	
	DMA_DCR0 |= DMA_DCR_DINC_MASK;	
	DMA_DCR0 |= DMA_DCR_DSIZE(10);
        }
	DMA_DCR0 |= DMA_DCR_EINT_MASK;	
	NVIC_EnableIRQ(DMA0_IRQn);
	__enable_irq;
	DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
	DMA_DCR0 |= DMA_DCR_START_MASK;


}

void memset_dma(uint8_t *dst, uint32_t length)
{
	        uint32_t i;
                uint8_t j;
                uint16_t k;
		SIM_SCGC7 |= SIM_SCGC7_DMA_MASK;
		SIM_SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
		DMAMUX0_CHCFG0 &= ~DMAMUX_CHCFG_ENBL_MASK;
		DMA_DSR_BCR0 |= DMA_DSR_BCR_DONE_MASK;
              if(length == i)
            {
		DMA_SAR0 =  &i;
		DMA_DAR0 =  dst;
        	DMA_DSR_BCR0 |= length;				
		DMA_DCR0 &= DMA_DCR_SINC_MASK;		
		DMA_DCR0 |= DMA_DCR_SSIZE(0);		
		DMA_DCR0 |= DMA_DCR_DINC_MASK;		
		DMA_DCR0 |= DMA_DCR_DSIZE(0);		
             }
             
             else if(length == j)
           {
                DMA_SAR0 =  &j;
		DMA_DAR0 =  dst;
        	DMA_DSR_BCR0 |= length;				
		DMA_DCR0 &= DMA_DCR_SINC_MASK;		
		DMA_DCR0 |= DMA_DCR_SSIZE(1);		
		DMA_DCR0 |= DMA_DCR_DINC_MASK;		
		DMA_DCR0 |= DMA_DCR_DSIZE(1);		
		
            }
            else( length == k)
           {
                DMA_SAR0 =  &k;
		DMA_DAR0 =  dst;
        	DMA_DSR_BCR0 |= length;				
		DMA_DCR0 &= DMA_DCR_SINC_MASK;		
		DMA_DCR0 |= DMA_DCR_SSIZE(10);		
		DMA_DCR0 |= DMA_DCR_DINC_MASK;		
		DMA_DCR0 |= DMA_DCR_DSIZE(10);		
		
             }
	        DMA_DCR0 |= DMA_DCR_EINT_MASK;		
		NVIC_EnableIRQ(DMA0_IRQn);
		__enable_irq;
		DMAMUX0_CHCFG0 |= DMAMUX_CHCFG_ENBL_MASK;
		DMA_DCR0 |= DMA_DCR_START_MASK;
}




