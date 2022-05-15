%% 
function updatedBuffer = fillArray(index, inBuffer)
    test_DUMMY_VALUE = 10000; 
    updatedBuffer = zeros(1, length(inBuffer));
	for i = 1:1:length(inBuffer)
		if (i == index)
			continue;
        end
		inBuffer(i) = test_DUMMY_VALUE;
    end
    updatedBuffer = inBuffer;
    
end

