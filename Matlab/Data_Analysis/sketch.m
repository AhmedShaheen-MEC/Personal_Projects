function sketch(a_r1,a_r2,a_h,p_r1,p_r2,p_h,tv_step,eta_step,p,s)
    x_a=[0 a_r1 a_r2 0];
    y_a=[0 0 a_h a_h];
    
    x_iw=[0 p_r1 p_r2 0];
    y_iw=[y_a(end) y_a(end) [p_h p_h]+y_a(:,end-1:end)];
    
    
    plot(x_a,y_a,'Color','k','LineWidth',1)
    hold on
    num2str(tv_step)
    title("Hammer design with target value: "+num2str(tv_step)+" and efficiency of: " +num2str(eta_step))
    plot(x_iw,y_iw,'Color','r','LineWidth',1.2)
    lgd=legend('Anvil','Impacr weight','Location','BestOutside')
    if p~=0
        lgd.Title.String = "Hammer components of p "+num2str(p)+" for step "+int2str(s) ;
    end
    lgd.AutoUpdate='off'
    plot(-x_a,y_a,'Color','k','LineWidth',1)
    plot(-x_iw,y_iw,'Color','r','LineWidth',1.2)
      set(gca,'yTick',[0:0.4:2,3:4:16]);
      hold off
      
end
