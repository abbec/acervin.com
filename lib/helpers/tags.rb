module Tags
  
  require 'set'
  
  def tag_list
    Set.new(@items.map{ |i| i[:tags] }.flatten)
  end

end
