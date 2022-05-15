function averagedValue = averageValue( new_value, buffer)
	sum = 0.0;
	valid_samples = 0;
    test_DUMMY_VALUE = 10000;
	for i = 1:1:length(buffer)
		if (buffer(i) == test_DUMMY_VALUE)
			continue;
        end
		sum = sum +  buffer(i);
		valid_samples = valid_samples +1;
    end
	averagedValue = (sum + new_value) / (valid_samples + 1);
end
