module Colorize
  def colorize_start(language)
    "<div class=\"highlight\"><pre><code class=\"language-#{language}\">"
  end

  def colorize_end
    "</code></pre></div>"
  end
end
