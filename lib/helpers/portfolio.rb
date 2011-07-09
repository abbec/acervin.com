module Portfolio

  def sort_portfolio(items)
    items = items.sort{|x,y| y[:year].to_i <=> x[:year].to_i}

    year = -1

    per_year = Array.new

    items.each do |i|
      if i[:year] != year
        year = i[:year]
        per_year.push(Array.new)
      end
      
      per_year.last.push(i)
    end

    per_year

  end

  def get_images(item, size)
    
    images = Array.new

    small = @items.select { |i| i.identifier =~ %r{#{item.identifier}img/small/[^/]+/$}}
    large = @items.select { |i| i.identifier =~ %r{#{item.identifier}img/large/[^/]+/$}}

    small.each_with_index do |s, i|
      h = Hash.new

      h[:small] = s
      h[:large] = large[i]

      images.push(h)

    end

    images

  end

end
