function[r1,r2,h]= setParameters(p_step)

r1=p_step(1);
 
    if length(p_step) > 2
    h= p_step(3);
    r2= p_step(2);
    else
    h= p_step(2);    
    r2=r1;
    end 
end    
