%% 
function [updatedBuffer] = fillArray(index, buffer)
    test_DUMMY_VALUE = 10000; 
	for i = 1:1:length(buffer)
		if (i == index)
			continue;
        end
		buffer(i) = test_DUMMY_VALUE;
    end
    updatedBuffer = buffer;
end

